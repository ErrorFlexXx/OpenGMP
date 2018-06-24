#pragma once

#include <list>
#include <string>
#include "script.hpp"

/**
 * @brief The ScriptController class manages scripts.
 *   The ScriptController manages all registered scripts and script functions.
 */
class ScriptController
{
public:
    /**
     * @brief LoadLuaScript method to load a lua script with given filename.
     * @param filename of the script to load.
     * @return true on success, false otherwise.
     */
    static void LoadLuaScript(const char *filename);

    /**
     * @brief LoadPythonScript method to load a python script with given filename.
     * @param filename of the script to load.
     * @return true on success, false otherwise.
     */
    static void LoadPythonScript(const char *filename);

    /**
     * @brief LoadScriptsFromDir loads scripts with known script extensions.
     * @param dir fullpath of script dir to search for scripts.
     */
    static void LoadScriptsFromDir(std::string &dir);

    /**
     * @brief UnloadScript unloads a script with the given filename.
     * @param script filename of the script to unload.
     * @return true on success, false otherwise.
     */
    static bool UnloadScript(std::string &filename);

    /**
     * @brief RegisterClass registers a class to be available in scripts.
     * @param metaName meta name defined in GDefineMetaClass Macro/Function
     * @param classname name of class as it will be available in scripts.
     */
    static void RegisterClass(const std::string &classname);

    /**
     * @brief GetRegisteredClasses returns a list of pairs with metaClassNames, classnames definitions.
     *  Most probably used as support function in Script class.
     * @return std::list<std::pair<std::string, std::string>>
     */
    static const std::list<std::pair<const std::string, const std::string>> &GetRegisteredClasses();

    static void InvokeScriptFunction(const std::string &functionName);

private:
    ScriptController(); //Abstract class - The one and only script controller
    static std::list<Script*> m_registeredScripts; //!< Container to hold loaded script objects in.
    static std::list<std::pair<const std::string, const std::string>> m_registeredClasses; //!< Container of registered meta classes.
};
