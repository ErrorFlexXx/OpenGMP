#pragma once

#include <string>
#include <cpgf/metatraits/gmetaconverter_string.h>
#include <cpgf/gmetadefine.h>
#include <cpgf/scriptbind/gscriptbind.h>
#include <cpgf/scriptbind/gscriptbindutil.h>
#include <cpgf/gscopedinterface.h>

namespace OpenGMP
{
    class GameServer;
    class ServerClient;

    /**
     * @brief The IScript class is an interface for a script implementation.
     *  Each Script Object has to implement the following structure
     */
    class Script
    {
    public:
        Script(GameServer &gameServer, std::string &filename);

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
         * @brief InvokePre preparation task to invoke a function on a script.
         */
        virtual void InvokePre() {}

        /**
         * @brief InvokePost finalization task to after invoking of a function on a script.
         */
        virtual void InvokePost() {}

        template<typename... Parameters>
        void InvokeScriptFunction(const std::string &functionName, Parameters && ... parameters)
        {
            InvokePre();
            invokeScriptFunction(m_binding->get(), functionName.c_str(), std::forward<Parameters>(parameters)...);
            InvokePost();
        }

        /**
         * @brief filename getter of filename attribute.
         */
        std::string fullFilePath() const;

    protected:
        /**
         * @brief IScript constructor for the base object.
         * @param filename filename that represents the script.
         */
        Script(std::string &fullFilePath);

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

        std::string m_fullFilePath; //!< Filename of the loaded script.
        std::string m_filename;     //!< Filename without path & extension
        cpgf::GScopedInterface<cpgf::IMetaService> *m_service; //!< service object for this script instance.
        cpgf::GScopedPointer<cpgf::GScriptObject> *m_binding; //!< binding for this script.
        cpgf::GScopedInterface<cpgf::IScriptObject> *m_scope; //!< scope object for this script instance.
        GameServer &m_gameServer;
    };
}

