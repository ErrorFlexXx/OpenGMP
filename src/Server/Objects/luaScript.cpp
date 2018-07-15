#include "luaScript.hpp"
#include "../gameServer.hpp"
#include <utils/logger.h>
#include <cpgf/scriptbind/gluarunner.h>
#include <cpgf/scriptbind/gluabind.h>

using namespace std;
using namespace cpgf;
using namespace OpenGMP;
using namespace OpenGMP::Objects;

LuaScript::LuaScript(GameServer &gameServer, std::string filename)
    : Script(gameServer, filename)
{
}

LuaScript::~LuaScript()
{
}

bool LuaScript::Load()
{
    m_lState = lua_open();
    luaL_openlibs(m_lState);
    SetLuaPath(string(m_gameServer.scriptDirectory).append("?.lua"));

    //lua_call(m_lState, 0, LUA_MULTRET);
    m_service = new GScopedInterface<IMetaService>(createDefaultMetaService());
    m_binding = new GScopedPointer<GScriptObject>(createLuaScriptObject(m_service->get(), m_lState));
    m_scope = new GScopedInterface<IScriptObject>(m_binding->get()->createScriptObject("OpenGMP").toScriptObject());

    m_binding->get()->bindCoreService("cpgf", nullptr);

    LoadClasses();
    LoadGlobals();

    int result = luaL_loadfile(m_lState, m_fullFilePath.c_str());
    if(result != 0)
    {
        LogWarn() << "Loading failed for lua script: " << m_filename.c_str() << "\r\nError: " << lua_tostring(m_lState, -1);
        lua_pop(m_lState, 1);
        return false;
    }
    int lscript = luaL_dofile(m_lState, m_fullFilePath.c_str());
    if(lscript != 0)
    {
        LogWarn() << "Loading failed for lua script: " << m_filename.c_str() << "\r\nError: " << lua_tostring(m_lState, -1);
        lua_pop(m_lState, 1);
        return false;
    }

    return true;
}

bool LuaScript::Unload()
{
    lua_close(m_lState);
    return true;
}

int LuaScript::SetLuaPath(const std::string &path )
{
    lua_getglobal(m_lState, "package" );
    lua_getfield(m_lState, -1, "path" ); // get field "path" from table at top of stack (-1)
    std::string cur_path = lua_tostring( m_lState, -1 ); // grab path string from top of stack
    cur_path.append( ";" ); // do your path magic here
    cur_path.append( path );
    lua_pop(m_lState, 1 ); // get rid of the string on the stack we just pushed
    lua_pushstring(m_lState, cur_path.c_str() ); // push the new one
    lua_setfield(m_lState, -2, "path" ); // set the field "path" in table at -2 with value at top of stack
    lua_pop(m_lState, 1 ); // get rid of package table from top of stack
    return 0;
}
