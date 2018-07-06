#pragma once

#include <list>
#include <string>
#include "../Objects/script.hpp"

namespace OpenGMP
{
    namespace Objects
    {
        class ServerClient;
    }

    namespace Systems
    {
        /**
         * @brief The ScriptSystem class manages scripts.
         *   The ScriptController manages all registered scripts and script functions.
         */
        class ScriptSystem
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
             * @brief RegisterGlobal registers a global function or var. to be avail. in scripts.
             * @param name name that shall the global be called in scripts.
             */
            static void RegisterGlobal(const std::string &name);

            /**
             * @brief GetRegisteredClasses returns a list of pairs with metaClassNames, classnames definitions.
             *  Mostly used as support function in Script class.
             * @return std::list<std::pair<std::string, std::string>>
             */
            static const std::list<std::pair<const std::string, const std::string>> &GetRegisteredClasses();

            /**
             * @brief GetRegisteredGlobals returns a list of names for registered globals.
             *   Mostly used as support function in Script class.
             * @return std::list<std::string> a list of names.
             */
            static const std::list<std::string> &GetRegisteredGlobals();

            /**
             * @brief InvokeScriptFunction calls a script function in all registered scripts.
             * @param functionName of the function, that should be called.
             */
            static void InvokeScriptFunction(const std::string &functionName);

            /**
             * @brief InvokeScriptFunctionParamServerClient calls a script function in all registered scripts with matching name.
             * @param functionName name of the function, that should be called.
             * @param serverClient reference to ServerClient object this callback shall work with.
             */
            static void InvokeScriptFunctionParamServerClient(const std::string &functionName,
                                                          Objects::ServerClient &serverClient);

        private:
            ScriptSystem(); //Abstract class - The one and only script controller
            static std::list<Objects::Script*> m_registeredScripts; //!< Container to hold loaded script objects in.
            static std::list<std::pair<const std::string, const std::string>> m_registeredClasses; //!< Container with names of registered meta classes.
            static std::list<std::string> m_registeredGlobals; //!< Container with names of registered globals
        };
    }
}
