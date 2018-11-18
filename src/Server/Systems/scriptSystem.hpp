#pragma once

#include <list>
#include <string>
#include "../Objects/script.hpp"

namespace OpenGMP
{
    class GameServer;
    class ServerClient;

    /**
     * @brief The ScriptSystem class manages scripts.
     *   The ScriptController manages all registered scripts and script functions.
     */
    class ScriptSystem
    {
    public:
        ScriptSystem(GameServer &gameServer);

        void SetupMetaData();

        /**
         * @brief LoadLuaScript method to load a lua script with given filename.
         * @param filename of the script to load.
         * @return true on success, false otherwise.
         */
        void LoadLuaScript(const char *filename);

        /**
         * @brief LoadPythonScript method to load a python script with given filename.
         * @param filename of the script to load.
         * @return true on success, false otherwise.
         */
        void LoadPythonScript(const char *filename);

        /**
         * @brief LoadScriptsFromDir loads scripts with known script extensions.
         * @param dir fullpath of script dir to search for scripts.
         */
        void LoadScriptsFromDir(std::string &dir);

        /**
         * @brief UnloadScripts
         *  unloads all loaded scripts.
         */
        void UnloadScripts();

        /**
         * @brief UnloadScript unloads a script with the given filename.
         * @param script filename of the script to unload.
         * @return true on success, false otherwise.
         */
        bool UnloadScript(std::string &filename);

        /**
         * @brief RegisterClass registers a class to be available in scripts.
         * @param metaName meta name defined in GDefineMetaClass Macro/Function
         * @param classname name of class as it will be available in scripts.
         */
        void RegisterClass(std::string classname);

        /**
         * @brief RegisterGlobal registers a global function or var. to be avail. in scripts.
         * @param name name that shall the global be called in scripts.
         */
        void RegisterGlobal(std::string name);

        /**
         * @brief GetRegisteredClasses returns a list of pairs with metaClassNames, classnames definitions.
         *  Mostly used as support function in Script class.
         * @return std::list<std::pair<std::string, std::string>>
         */
        const std::list<std::string> &GetRegisteredClasses();

        /**
         * @brief GetRegisteredGlobals returns a list of names for registered globals.
         *   Mostly used as support function in Script class.
         * @return std::list<std::string> a list of names.
         */
        const std::list<std::string> &GetRegisteredGlobals();

        /**
         * @brief InvokeScriptFunction calls a script function in all registered scripts with matching name.
         * @param functionName name of the function, that should be called.
         */
        template<typename... Parameters>
        void InvokeScriptFunction(const std::string &functionName,
                                  Parameters && ... parameters)
        {
            for(Script *script : m_registeredScripts)
            {
                try
                {
                    script->InvokeScriptFunction(functionName, std::forward<Parameters>(parameters)...);
                }
                catch(std::exception & ex)
                {
                    //LogWarn() << ex.what();
                }
            }
        }

    private:
        std::list<Script*> m_registeredScripts; //!< Container to hold loaded script objects in.
        std::list<std::string> m_registeredClasses; //!< Container with names of registered meta classes.
        std::list<std::string> m_registeredGlobals; //!< Container with names of registered globals
        GameServer &gameServer; //!< The GameServer instance this System acts for.
        static bool metaInited;
    };
}
