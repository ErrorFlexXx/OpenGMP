#include "scriptSystem.hpp"
#include <tinydir.h>
#include <utils/logger.h>
#include "../Objects/luaScript.hpp"
#include "../Objects/pythonScript.hpp"

//Script library includes:
#include <cpgf/metatraits/gmetaconverter_string.h>
#include <cpgf/gmetadefine.h>
#include <cpgf/goutmain.h>
//Script interface classes:
#include "../Objects/serverClient.hpp"
#include <Shared/Components/authData.hpp>
#include <Shared/Components/netId.hpp>
#include <Shared/Components/id.hpp>
#include "../gameServer.hpp"
#include "../Systems/loginSystem.hpp"
#include "../Systems/mySqlSystem.hpp"

using namespace std;
using namespace OpenGMP;
using namespace OpenGMP::Components;
using namespace OpenGMP::Objects;
using namespace OpenGMP::Systems;

//Statics attributes
std::list<Script*> ScriptSystem::m_registeredScripts;
std::list<std::pair<const string, const string>> ScriptSystem::m_registeredClasses;

void ScriptSystem::LoadLuaScript(const char *filename)
{
    m_registeredScripts.push_back(new LuaScript(string(filename)));
    if(!m_registeredScripts.back()->Load())
        LogError() << "LoadLuaScript failed!";
}

void ScriptSystem::LoadPythonScript(const char *filename)
{
    m_registeredScripts.push_back(new PythonScript(string(filename)));
    if(!m_registeredScripts.back()->Load())
        LogError() << "LoadPythonScript failed!";
}

void ScriptSystem::LoadScriptsFromDir(std::string &dir)
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

bool ScriptSystem::UnloadScript(std::string &filename)
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

void ScriptSystem::RegisterClass(const string &classname)
{
    string assembledMetaName("method::");
    assembledMetaName.append(classname);

    m_registeredClasses.push_back(
                std::make_pair(assembledMetaName,
                               classname));
}

const std::list<std::pair<const std::string, const std::string>> &ScriptSystem::GetRegisteredClasses()
{
    return m_registeredClasses;
}

void ScriptSystem::InvokeScriptFunction(const std::string &functionName)
{
    for(Script *script : m_registeredScripts)
    {
        try
        {
            script->InvokeScriptFunction(functionName);
        }
        catch(...)
        {}
    }
}

void ScriptSystem::InvokeScriptFunctionParamServerClient(const std::string &functionName,
                                                         ServerClient &serverClient)
{
    for(Script *script : m_registeredScripts)
    {
        try
        {
            script->InvokeScriptFunctionParamServerClient(functionName, serverClient);
        }
        catch(...)
        {}
    }
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
    ScriptSystem::RegisterClass(std::string("GameServer"));

    GDefineMetaClass<AuthData>
            ::define("method::AuthData")
            //._constructor<void *(const string, const string)>()
            ._property("loginname", &AuthData::GetLoginname, &AuthData::SetLoginname)
            ._property("password", &AuthData::GetPassword, &AuthData::SetPassword)
            ._property("hddSerial", &AuthData::GetHddSerial, &AuthData::SetHddSerial)
            ._property("macAddress", &AuthData::GetMacAddress, &AuthData::SetMacAddress)
            ;
    ScriptSystem::RegisterClass(std::string("AuthData"));

    GDefineMetaClass<NetId>
            ::define("method::NetId")
            ._property("rakNetId", &NetId::GetRakNetId, &NetId::SetRakNetId)
            ;
    ScriptSystem::RegisterClass(std::string("NetId"));

    GDefineMetaClass<Id>
            ::define("method::Id")
            ._property("id", &Id::GetId, &Id::SetId)
            ;
    ScriptSystem::RegisterClass(std::string("Id"));

    GDefineMetaClass<ServerClient>
            ::define("method::ServerClient")
            //._constructor<void *(const string, const string)>()
            //._method("Shutdown", &GameServer::Shutdown)
            ._property("authData", &ServerClient::GetAuthData, &ServerClient::SetAuthData)
            ;
    ScriptSystem::RegisterClass(std::string("ServerClient"));

    GDefineMetaClass<MySqlSystem>
            ::define("method::MySqlSystem")
            ._method("TestFunctionVariadic", &MySqlSystem::TestFunctionVariadic)
            ;
    ScriptSystem::RegisterClass(std::string("MySqlSystem"));
}
