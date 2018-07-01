#include "luaScript.hpp"
#include <utils/logger.h>
#include <cpgf/scriptbind/gluarunner.h>
#include <cpgf/scriptbind/gluabind.h>

using namespace std;
using namespace cpgf;
using namespace OpenGMP::Objects;

LuaScript::LuaScript(std::string filename)
    : Script(filename)
{
}

LuaScript::~LuaScript()
{
}

bool LuaScript::Load()
{
    m_lState = luaL_newstate();
    luaL_openlibs(m_lState);
    int result = luaL_loadfile(m_lState, m_filename.c_str());
    if(result != 0)
    {
        LogError() << "Read failed for lua script file: " << m_filename.c_str();
        return false;
    }
    lua_call(m_lState, 0, LUA_MULTRET);
    m_service = new GScopedInterface<IMetaService>(createDefaultMetaService());
    m_binding = new GScopedPointer<GScriptObject>(createLuaScriptObject(m_service->get(), m_lState));
    m_scope = new GScopedInterface<IScriptObject>(m_binding->get()->createScriptObject("OpenGMP").toScriptObject());

    LoadClasses();

    return true;
}

bool LuaScript::Unload()
{
    lua_close(m_lState);
    return true;
}
