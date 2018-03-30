#pragma once

#include <string>
#include "script.hpp"

class lua_State;

class LuaScript : public Script
{
public:
    LuaScript(std::string filename);

    /**
     * @brief ~LuaScript virtual destructor -- Ćalled on Script::~Script.
     */
    virtual ~LuaScript();

    /**
     * @brief Load is a method to load and initalize the script.
     * @return true on success, false otherwise.
     */
    bool Load() override;

    /**
     * @brief Unload is a method, that unloads all resources of a script.
     * @return true on success, false otherwise.
     */
    bool Unload() override;

private:
    lua_State * m_lState; //!< Object of the lua instance.
};
