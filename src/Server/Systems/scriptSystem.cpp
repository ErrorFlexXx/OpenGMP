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
#include <Shared/Components/color.hpp>
#include <Shared/Components/notificationText.hpp>
#include "../gameServer.hpp"
#include "../Systems/loginSystem.hpp"
#include "../Systems/scriptMysqlBindHelper.hpp"
#include <mysql/mysql.h>

using namespace std;
using namespace cpgf;
using namespace OpenGMP;

bool ScriptSystem::metaInited = false;

ScriptSystem::ScriptSystem(GameServer &gameServer)
    : gameServer(gameServer)
{
    SetupMetaData();
}

void ScriptSystem::LoadLuaScript(const char *filename)
{
    m_registeredScripts.push_back(new LuaScript(gameServer, string(filename)));
    if(!m_registeredScripts.back()->Load())
    {
        LogError() << "LoadLuaScript failed!";
        delete m_registeredScripts.back();
        m_registeredScripts.pop_back();
    }
}

void ScriptSystem::LoadPythonScript(const char *filename)
{
    m_registeredScripts.push_back(new PythonScript(gameServer, string(filename)));
    if(!m_registeredScripts.back()->Load())
    {
        LogError() << "LoadPythonScript failed!";
        delete m_registeredScripts.back();
        m_registeredScripts.pop_back();
    }
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
}

bool ScriptSystem::UnloadScript(std::string &filename)
{
    bool result = false;
    const int equal = 0;

    for(auto i = m_registeredScripts.begin(); i != m_registeredScripts.end(); i++)
    {
        string checkFilename = (*i)->fullFilePath();

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
    m_registeredClasses.push_back(classname);
}

void ScriptSystem::RegisterGlobal(const string &name)
{
    m_registeredGlobals.push_back(
                name);
}

const std::list<const std::string> &ScriptSystem::GetRegisteredClasses()
{
    return m_registeredClasses;
}

const std::list<std::string> &ScriptSystem::GetRegisteredGlobals()
{
    return m_registeredGlobals;
}

size_t GetMysqlBindSize()
{
    return sizeof(MYSQL_BIND);
}

//Script interface registration:
void ScriptSystem::SetupMetaData()
{
    using namespace cpgf;

    //Global meta definitions:
    RegisterGlobal(std::string("mysql_init"));
    RegisterGlobal(std::string("mysql_real_connect"));
    RegisterGlobal(std::string("mysql_set_character_set"));
    RegisterGlobal(std::string("mysql_error"));
    RegisterGlobal(std::string("mysql_errno"));
    RegisterGlobal(std::string("mysql_close"));
    RegisterGlobal(std::string("mysql_info"));
    RegisterGlobal(std::string("mysql_hex_string"));
    RegisterGlobal(std::string("mysql_ping"));
    RegisterGlobal(std::string("mysql_select_db"));
    RegisterGlobal(std::string("mysql_warning_count"));
    RegisterGlobal(std::string("mysql_ping"));
    RegisterGlobal(std::string("mysql_change_user"));
    RegisterGlobal(std::string("mysql_get_character_set_info"));
    RegisterGlobal(std::string("mysql_get_client_info"));
    RegisterGlobal(std::string("mysql_get_client_version"));
    RegisterGlobal(std::string("mysql_get_host_info"));
    RegisterGlobal(std::string("mysql_get_proto_info"));
    RegisterGlobal(std::string("mysql_get_server_info"));
    RegisterGlobal(std::string("mysql_get_server_version"));
    RegisterGlobal(std::string("mysql_stat"));
    RegisterGlobal(std::string("mysql_insert_id"));
    //Mysql Result:
    RegisterGlobal(std::string("mysql_query"));
    RegisterGlobal(std::string("mysql_real_escape_string"));
    RegisterGlobal(std::string("mysql_data_seek"));
    RegisterGlobal(std::string("mysql_fetch_field"));
    RegisterGlobal(std::string("mysql_fetch_field_direct"));
    RegisterGlobal(std::string("mysql_fetch_fields"));
    RegisterGlobal(std::string("mysql_fetch_lengths"));
    RegisterGlobal(std::string("mysql_fetch_row"));
    RegisterGlobal(std::string("mysql_field_count"));
    RegisterGlobal(std::string("mysql_field_seek"));
    RegisterGlobal(std::string("mysql_field_tell"));
    RegisterGlobal(std::string("mysql_free_result"));
    RegisterGlobal(std::string("mysql_num_rows"));
    RegisterGlobal(std::string("mysql_more_results"));
    RegisterGlobal(std::string("mysql_next_result"));
    RegisterGlobal(std::string("mysql_num_fields"));
    RegisterGlobal(std::string("mysql_affected_rows"));
    RegisterGlobal(std::string("mysql_rollback"));
    RegisterGlobal(std::string("mysql_row_seek"));
    RegisterGlobal(std::string("mysql_row_tell"));
    //Mysql Statements:
    RegisterGlobal(std::string("mysql_stmt_init"));
    RegisterGlobal(std::string("mysql_stmt_prepare"));
    RegisterGlobal(std::string("mysql_stmt_bind_param"));
    RegisterGlobal(std::string("mysql_stmt_bind_result"));
    RegisterGlobal(std::string("mysql_stmt_execute"));
    RegisterGlobal(std::string("mysql_stmt_attr_get"));
    RegisterGlobal(std::string("mysql_stmt_attr_set"));
    RegisterGlobal(std::string("mysql_stmt_affected_rows"));
    RegisterGlobal(std::string("mysql_stmt_data_seek"));
    RegisterGlobal(std::string("mysql_stmt_error"));
    RegisterGlobal(std::string("mysql_stmt_errno"));
    RegisterGlobal(std::string("mysql_stmt_fetch"));
    RegisterGlobal(std::string("mysql_stmt_fetch_column"));
    RegisterGlobal(std::string("mysql_stmt_field_count"));
    RegisterGlobal(std::string("mysql_stmt_free_result"));
    RegisterGlobal(std::string("mysql_stmt_next_result"));
    RegisterGlobal(std::string("mysql_stmt_num_rows"));
    RegisterGlobal(std::string("mysql_stmt_param_count"));
    RegisterGlobal(std::string("mysql_stmt_reset"));
    RegisterGlobal(std::string("mysql_stmt_row_seek"));
    RegisterGlobal(std::string("mysql_stmt_row_tell"));
    RegisterGlobal(std::string("mysql_stmt_store_result"));
    RegisterGlobal(std::string("mysql_stmt_insert_id"));
    RegisterGlobal(std::string("mysql_stmt_close"));

    //Object oriented meta definitions:
    RegisterClass(std::string("GameServer"));
    RegisterClass(std::string("AuthData"));
    RegisterClass(std::string("NetId"));
    RegisterClass(std::string("Id"));
    RegisterClass(std::string("ServerClient"));
    RegisterClass(std::string("ScriptMysqlBindHelper"));
    //RegisterClass(std::string("MYSQL_BIND"));

    if(!ScriptSystem::metaInited)
    {
        ScriptSystem::metaInited = true; //Only do once

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

//        GDefineMetaClass<MYSQL_BIND>
//                ::define("MYSQL_BIND")
//                ._field("length", &MYSQL_BIND::length)
//                ._field("buffer", &MYSQL_BIND::buffer)
//                ._field("buffer_type", &MYSQL_BIND::buffer_type)
//                ._field("buffer_length", &MYSQL_BIND::buffer_length)
//                ._field("is_null", &MYSQL_BIND::is_null)
//                ._method("sizeof", &GetMysqlBindSize)
//        ;

        GDefineMetaClass<ScriptMysqlBindHelper>
                ::define("ScriptMysqlBindHelper")
                ._method("AddString", &ScriptMysqlBindHelper::AddString)
                ._method("AddInt", &ScriptMysqlBindHelper::AddInt)
                ._method("AddDouble", &ScriptMysqlBindHelper::AddDouble)
                ._method("ResetBinds", &ScriptMysqlBindHelper::ResetBinds)
                ._method("Bind", &ScriptMysqlBindHelper::Bind)
        ;

        GDefineMetaClass<GameServer>
                ::define("GameServer")
                //._constructor<void *(const string, const string)>()
                ._method("GetGameServerInstance", &GameServer::GetGameServerInstance)
                ._method("Shutdown", &GameServer::Shutdown)
                ;

        GDefineMetaClass<AuthData>
                ::define("AuthData")
                ._field("loginname", &AuthData::loginname)
                ._field("password", &AuthData::password)
                ._field("hddSerial", &AuthData::hddSerial)
                ._field("macAddress", &AuthData::macAddress)
                ;

        GDefineMetaClass<NetId>
                ::define("NetId")
                ._field("rakNetId", &NetId::rakNetId)
                ;

        GDefineMetaClass<Id>
                ::define("Id")
                ._field("id", &Id::id)
                ;

        GDefineMetaClass<ServerClient,Client,NetIdObject,IdObject>
                ::define("ServerClient")
                ._field("authData", &ServerClient::authData)
                ;

        GDefineMetaClass<Color>
                ::define("Color")
                ._field("r", &Color::r)
                ._field("g", &Color::g)
                ._field("b", &Color::b)
                ._field("a", &Color::a)
                ;

        GDefineMetaClass<NotificationText>
                ::define("NotificationText")
                ._field("text", &NotificationText::text)
                ._field("posY", &NotificationText::posY)
                ._field("color", &NotificationText::color)
                ._field("duration", &NotificationText::duration)
                ;
    }
}
