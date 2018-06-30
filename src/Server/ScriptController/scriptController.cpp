#include "scriptController.hpp"
#include <tinydir.h>
#include <utils/logger.h>
#include "luaScript.hpp"
#include "pythonScript.hpp"

//Script library includes:
#include <cpgf/metatraits/gmetaconverter_string.h>
#include <cpgf/gmetadefine.h>
#include <cpgf/goutmain.h>
//Script interface classes:
#include "../Objects/serverClient.hpp"
#include "../gameServer.hpp"
#include "../Systems/loginSystem.hpp"

using namespace std;
using namespace OpenGMP;

//Statics attributes
std::list<Script*> ScriptController::m_registeredScripts;
std::list<std::pair<const string, const string>> ScriptController::m_registeredClasses;

void ScriptController::LoadLuaScript(const char *filename)
{
    m_registeredScripts.push_back(new LuaScript(string(filename)));
    if(!m_registeredScripts.back()->Load())
        LogError() << "LoadLuaScript failed!";
}

void ScriptController::LoadPythonScript(const char *filename)
{
    m_registeredScripts.push_back(new PythonScript(string(filename)));
    if(!m_registeredScripts.back()->Load())
        LogError() << "LoadPythonScript failed!";
}

void ScriptController::LoadScriptsFromDir(std::string &dir)
{
    tinydir_dir directory;
    directory.has_next = 0; //Make the compiler happy -- has_next ist initialized :P

    tinydir_open(&directory, TINYDIR_STRING(dir.c_str()));
    while(directory.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&directory, &file);
        string extension(file.extension);
        if(extension.compare("lua") == 0)
        {
            LogInfo() << "Loading lua script: " << file.name;
            LoadLuaScript(file.path);
        }
        else if(extension.compare("py") == 0)
        {
            LogInfo() << "Loading python script: " << file.name;
            LoadPythonScript(file.path);
        }
        tinydir_next(&directory);
    }
    tinydir_close(&directory);

    InvokeScriptFunction("init");
}

bool ScriptController::UnloadScript(std::string &filename)
{
    bool result = false;
    const int equal = 0;

    for(auto i = m_registeredScripts.begin(); i != m_registeredScripts.end(); i++)
    {
        string checkFilename = (*i)->filename();

        if(equal == checkFilename.compare(filename))
        {
            result = true;
            result = result && (*i)->Unload();
            delete (*i);
            m_registeredScripts.erase(i--);
            break; //Expect only one script with given filename.
        }
    }
    return result;
}

void ScriptController::RegisterClass(const string &classname)
{
    string assembledMetaName("method::");
    assembledMetaName.append(classname);

    m_registeredClasses.push_back(
                std::make_pair(assembledMetaName,
                               classname));
}

const std::list<std::pair<const std::string, const std::string>> &ScriptController::GetRegisteredClasses()
{
    return m_registeredClasses;
}

void ScriptController::InvokeScriptFunction(const std::string &functionName)
{
    for(Script *script : m_registeredScripts)
        script->InvokeScriptFunction(functionName);
}

//Script interface registration:
G_AUTO_RUN_BEFORE_MAIN()
{
    using namespace cpgf;

    GDefineMetaClass<GameServer>
            ::define("method::GameServer")
            //._constructor<void *(const string, const string)>()
            ._method("GetGameServerInstance", &GameServer::GetGameServerInstance)
            ._method("Shutdown", &GameServer::Shutdown)
            //._property("testAttribute", &GameServer::GetTestAttribute, &GameServer::SetTestAttribute)
            ;
    ScriptController::RegisterClass(std::string("GameServer"));

}
