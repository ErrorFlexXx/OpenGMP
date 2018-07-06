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
#include <mysql/mysql.h>

using namespace std;
using namespace cpgf;
using namespace OpenGMP;
using namespace OpenGMP::Components;
using namespace OpenGMP::Objects;
using namespace OpenGMP::Systems;

//Statics attributes
std::list<Script*> ScriptSystem::m_registeredScripts;
std::list<std::pair<const string, const string>> ScriptSystem::m_registeredClasses;
std::list<std::string> ScriptSystem::m_registeredGlobals;

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
        try
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
        }
        catch(std::exception &ex)
        {
            LogWarn() << ex.what();
        }

        tinydir_next(&directory);
    }
    tinydir_close(&directory);

    InvokeScriptFunction("Init");
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

void ScriptSystem::RegisterGlobal(const string &name)
{
    m_registeredGlobals.push_back(
                name);
}

const std::list<std::pair<const std::string, const std::string>> &ScriptSystem::GetRegisteredClasses()
{
    return m_registeredClasses;
}

const std::list<std::string> &ScriptSystem::GetRegisteredGlobals()
{
    return m_registeredGlobals;
}

void ScriptSystem::InvokeScriptFunction(const std::string &functionName)
{
    for(Script *script : m_registeredScripts)
    {
        try
        {
            script->InvokeScriptFunction(functionName);
        }
        catch(std::exception & ex)
        {
            LogWarn() << ex.what();
        }
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
        catch(std::exception & ex)
        {
            LogWarn() << ex.what();
        }
    }
}

//Script interface registration:
G_AUTO_RUN_BEFORE_MAIN()
{
    using namespace cpgf;

    GDefineMetaGlobal()

            //Mysql Handler:
            ._method("mysql_init", &mysql_init)
            ._method("mysql_real_connect", &mysql_real_connect)
            ._method("mysql_set_character_set", &mysql_set_character_set)
            ._method("mysql_error", &mysql_error)
            ._method("mysql_errno", &mysql_errno)
            ._method("mysql_close", &mysql_close)
            ._method("mysql_info", &mysql_info)
            ._method("mysql_hex_string", &mysql_hex_string)
            ._method("mysql_ping", &mysql_ping)
            ._method("mysql_select_db", &mysql_select_db)
            ._method("mysql_warning_count", &mysql_warning_count)
            ._method("mysql_ping", &mysql_ping)
            ._method("mysql_change_user", &mysql_change_user)
            ._method("mysql_get_character_set_info", &mysql_get_character_set_info)
            ._method("mysql_get_client_info", &mysql_get_client_info)
            ._method("mysql_get_client_version", &mysql_get_client_version)
            ._method("mysql_get_host_info", &mysql_get_host_info)
            ._method("mysql_get_proto_info", &mysql_get_proto_info)
            ._method("mysql_get_server_info", &mysql_get_server_info)
            ._method("mysql_get_server_version", &mysql_get_server_version)
            ._method("mysql_stat", &mysql_stat)
            ._method("mysql_insert_id", &mysql_insert_id)
            //Mysql Result:
            ._method("mysql_query", &mysql_query)
            ._method("mysql_real_escape_string", &mysql_real_escape_string)
            ._method("mysql_data_seek", &mysql_data_seek)
            ._method("mysql_fetch_field", &mysql_fetch_field)
            ._method("mysql_fetch_field_direct", &mysql_fetch_field_direct)
            ._method("mysql_fetch_fields", &mysql_fetch_fields)
            ._method("mysql_fetch_lengths", &mysql_fetch_lengths)
            ._method("mysql_fetch_row", &mysql_fetch_row)
            ._method("mysql_field_count", &mysql_field_count)
            ._method("mysql_field_seek", &mysql_field_seek)
            ._method("mysql_field_tell", &mysql_field_tell)
            ._method("mysql_free_result", &mysql_free_result)
            ._method("mysql_num_rows", &mysql_num_rows)
            ._method("mysql_more_results", &mysql_more_results)
            ._method("mysql_next_result", &mysql_next_result)
            ._method("mysql_num_fields", &mysql_num_fields)
            ._method("mysql_affected_rows", &mysql_affected_rows)
            ._method("mysql_rollback", &mysql_rollback)
            ._method("mysql_row_seek", &mysql_row_seek)
            ._method("mysql_row_tell", &mysql_row_tell)
            //Mysql Statements:
            ._method("mysql_stmt_init", &mysql_stmt_init)
            ._method("mysql_stmt_prepare", &mysql_stmt_prepare)
            ._method("mysql_stmt_bind_param", &mysql_stmt_bind_param)
            ._method("mysql_stmt_bind_result", &mysql_stmt_bind_result)
            ._method("mysql_stmt_execute", &mysql_stmt_execute)
            ._method("mysql_stmt_attr_get", &mysql_stmt_attr_get)
            ._method("mysql_stmt_attr_set", &mysql_stmt_attr_set)
            ._method("mysql_stmt_affected_rows", &mysql_stmt_affected_rows)
            ._method("mysql_stmt_data_seek", &mysql_stmt_data_seek)
            ._method("mysql_stmt_error", &mysql_stmt_error)
            ._method("mysql_stmt_errno", &mysql_stmt_errno)
            ._method("mysql_stmt_fetch", &mysql_stmt_fetch)
            ._method("mysql_stmt_fetch_column", &mysql_stmt_fetch_column)
            ._method("mysql_stmt_field_count", &mysql_stmt_field_count)
            ._method("mysql_stmt_free_result", &mysql_stmt_free_result)
            ._method("mysql_stmt_next_result", &mysql_stmt_next_result)
            ._method("mysql_stmt_num_rows", &mysql_stmt_num_rows)
            ._method("mysql_stmt_param_count", &mysql_stmt_param_count)
            ._method("mysql_stmt_reset", &mysql_stmt_reset)
            ._method("mysql_stmt_row_seek", &mysql_stmt_row_seek)
            ._method("mysql_stmt_row_tell", &mysql_stmt_row_tell)
            ._method("mysql_stmt_store_result", &mysql_stmt_store_result)
            ._method("mysql_stmt_insert_id", &mysql_stmt_insert_id)
            ._method("mysql_stmt_close", &mysql_stmt_close)
    ;
    ScriptSystem::RegisterGlobal(std::string("mysql_init"));
    ScriptSystem::RegisterGlobal(std::string("mysql_real_connect"));
    ScriptSystem::RegisterGlobal(std::string("mysql_set_character_set"));
    ScriptSystem::RegisterGlobal(std::string("mysql_error"));
    ScriptSystem::RegisterGlobal(std::string("mysql_errno"));
    ScriptSystem::RegisterGlobal(std::string("mysql_close"));
    ScriptSystem::RegisterGlobal(std::string("mysql_info"));
    ScriptSystem::RegisterGlobal(std::string("mysql_hex_string"));
    ScriptSystem::RegisterGlobal(std::string("mysql_ping"));
    ScriptSystem::RegisterGlobal(std::string("mysql_select_db"));
    ScriptSystem::RegisterGlobal(std::string("mysql_warning_count"));
    ScriptSystem::RegisterGlobal(std::string("mysql_ping"));
    ScriptSystem::RegisterGlobal(std::string("mysql_change_user"));
    ScriptSystem::RegisterGlobal(std::string("mysql_get_character_set_info"));
    ScriptSystem::RegisterGlobal(std::string("mysql_get_client_info"));
    ScriptSystem::RegisterGlobal(std::string("mysql_get_client_version"));
    ScriptSystem::RegisterGlobal(std::string("mysql_get_host_info"));
    ScriptSystem::RegisterGlobal(std::string("mysql_get_proto_info"));
    ScriptSystem::RegisterGlobal(std::string("mysql_get_server_info"));
    ScriptSystem::RegisterGlobal(std::string("mysql_get_server_version"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stat"));
    ScriptSystem::RegisterGlobal(std::string("mysql_insert_id"));
    //Mysql Result:
    ScriptSystem::RegisterGlobal(std::string("mysql_query"));
    ScriptSystem::RegisterGlobal(std::string("mysql_real_escape_string"));
    ScriptSystem::RegisterGlobal(std::string("mysql_data_seek"));
    ScriptSystem::RegisterGlobal(std::string("mysql_fetch_field"));
    ScriptSystem::RegisterGlobal(std::string("mysql_fetch_field_direct"));
    ScriptSystem::RegisterGlobal(std::string("mysql_fetch_fields"));
    ScriptSystem::RegisterGlobal(std::string("mysql_fetch_lengths"));
    ScriptSystem::RegisterGlobal(std::string("mysql_fetch_row"));
    ScriptSystem::RegisterGlobal(std::string("mysql_field_count"));
    ScriptSystem::RegisterGlobal(std::string("mysql_field_seek"));
    ScriptSystem::RegisterGlobal(std::string("mysql_field_tell"));
    ScriptSystem::RegisterGlobal(std::string("mysql_free_result"));
    ScriptSystem::RegisterGlobal(std::string("mysql_num_rows"));
    ScriptSystem::RegisterGlobal(std::string("mysql_more_results"));
    ScriptSystem::RegisterGlobal(std::string("mysql_next_result"));
    ScriptSystem::RegisterGlobal(std::string("mysql_num_fields"));
    ScriptSystem::RegisterGlobal(std::string("mysql_affected_rows"));
    ScriptSystem::RegisterGlobal(std::string("mysql_rollback"));
    ScriptSystem::RegisterGlobal(std::string("mysql_row_seek"));
    ScriptSystem::RegisterGlobal(std::string("mysql_row_tell"));
    //Mysql Statements:
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_init"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_prepare"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_bind_param"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_bind_result"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_execute"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_attr_get"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_attr_set"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_affected_rows"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_data_seek"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_error"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_errno"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_fetch"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_fetch_column"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_field_count"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_free_result"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_next_result"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_num_rows"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_param_count"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_reset"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_row_seek"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_row_tell"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_store_result"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_insert_id"));
    ScriptSystem::RegisterGlobal(std::string("mysql_stmt_close"));

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
}
