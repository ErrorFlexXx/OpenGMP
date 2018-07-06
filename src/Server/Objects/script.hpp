#pragma once

#include <string>
#include <cpgf/metatraits/gmetaconverter_string.h>
#include <cpgf/gmetadefine.h>
#include <cpgf/scriptbind/gscriptbind.h>
#include <cpgf/scriptbind/gscriptbindutil.h>
#include <cpgf/gscopedinterface.h>

namespace OpenGMP
{
    namespace Objects
    {
        class ServerClient;
    }

    namespace Objects
    {
        /**
         * @brief The IScript class is an interface for a script implementation.
         *  Each Script Object has to implement the following structure
         */
        class Script
        {
        public:
            /**
             * @brief ~Script virtual destructor: Call destructor of childs on deletion.
             */
            virtual ~Script();

            /**
             * @brief Load is a method to load and initalize the script.
             * @return true on success, false otherwise.
             */
            virtual bool Load() = 0;

            /**
             * @brief Unload is a method, that unloads all resources of a script.
             * @return true on success, false otherwise.
             */
            virtual bool Unload() = 0;

            /**
             * @brief InvokeScriptFunction calls a script function in all registered scripts with matching name
             * @param functionName to be called
             */
            void InvokeScriptFunction(const std::string &functionName);

            /**
             * @brief InvokeScriptFunctionParamServerClient calls a script function in all registered scripts with matching name.
             * @param functionName functionName  to be called
             * @param serverClient reference to ServerClient object this callback shall work with.
             */
            void InvokeScriptFunctionParamServerClient(const std::string &functionName,
                                                       Objects::ServerClient &serverClient);

            /**
             * @brief filename getter of filename attribute.
             */
            std::string filename() const;

        protected:
            /**
             * @brief IScript constructor for the base object.
             * @param filename filename that represents the script.
             */
            Script(std::string &filename);

            /**
             * @brief ReadStringFromFile reads a whole file into a string varible.
             * @param fileName name of file to read data from.
             * @param outContent pointer to string to be filled with contents.
             * @return true the whole file was read, false otherwise.
             */
            bool ReadStringFromFile(const std::string & fileName, std::string * outContent);

            /**
             * @brief LoadClasses registers all meta classes for a cpgf script instance to publish definitions.
             * @return atm. always true.
             */
            bool LoadClasses();

            /**
             * @brief LoadGlobals registers all meta globals for a cpgf script instance to publish definitions.
             * @return atm. always true.
             */
            bool LoadGlobals();

            std::string m_filename; //!< Filename of the loaded script.
            cpgf::GScopedInterface<cpgf::IMetaService> *m_service; //!< service object for this script instance.
            cpgf::GScopedPointer<cpgf::GScriptObject> *m_binding; //!< binding for this script.
            cpgf::GScopedInterface<cpgf::IScriptObject> *m_scope; //!< scope object for this script instance.
        };

    }
}

