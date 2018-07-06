#include "script.hpp"
#include "../Systems/scriptSystem.hpp"
#include "../Objects/serverClient.hpp"
#include <utils/logger.h>

using namespace std;
using namespace cpgf;
using namespace OpenGMP::Objects;
using namespace OpenGMP::Systems;

Script::Script(string &filename)
    : m_filename(filename)
{}

Script::~Script()
{
}

bool Script::LoadClasses()
{
    //Register all registered meta classes
    for(auto &metaClassPair : ScriptSystem::GetRegisteredClasses())
    {
        GScopedInterface<IMetaClass> metaClass(m_service->get()->findClassByName(metaClassPair.first.c_str()));
        scriptSetValue(m_binding->get(), metaClassPair.second.c_str(), GScriptValue::fromClass(metaClass.get()));
    }

    return true;
}

bool Script::LoadGlobals()
{
    GScopedInterface<IMetaModule> module(m_service->get()->getModuleAt(0));
    GScopedInterface<IMetaClass> global(module->getGlobalMetaClass());
    GScopedInterface<IMetaMethod> method;

    for(const std::string &name : ScriptSystem::GetRegisteredGlobals())
    {
        GScopedInterface<IMetaList> metaList(createMetaList());

        method.reset(global.get()->getMethod(name.c_str()));
        metaList.get()->add(method.get(), nullptr);
        scriptSetValue(m_binding->get(), name.c_str(), GScriptValue::fromOverloadedMethods(metaList.get()));
    }

    return true;
}

bool Script::ReadStringFromFile(const std::string & fileName, std::string * outContent)
{
    FILE * file = fopen(fileName.c_str(), "rb");
    if(file == NULL)
    {
        LogError() << "Cannot open file! fopen failed.";
        return false;
    }
    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);
    outContent->resize(length);
    size_t result = fread(&(*outContent)[0], 1, length, file);
    fclose(file);
    if(result != length)
        LogError() << "Requested " << length << " bytes, but got only " << result << "!";
    return result == length; //Read all requested bytes ?
}

std::string Script::filename() const
{
    return m_filename;
}

void Script::InvokeScriptFunction(const std::string &functionName)
{
    invokeScriptFunction(m_binding->get(), functionName.c_str());
}

void Script::InvokeScriptFunctionParamServerClient(const std::string &functionName,
                                               ServerClient &serverClient)
{
    invokeScriptFunction(m_binding->get(), functionName.c_str(), serverClient);
}
