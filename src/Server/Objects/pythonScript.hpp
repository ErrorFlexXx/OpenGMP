#pragma once

#include <string>
#include <cpgf/scriptbind/gpythonrunner.h>
#include <cpgf/scriptbind/gpythonbind.h>

#include "script.hpp"

namespace OpenGMP
{
    class GameServer;

    namespace Objects
    {
        class PythonScript : public Script
        {
        public:
            /**
             * @brief PythonScript constructs a PythonScript object and loads the code.
             * @param filename of the python script file
             */
            PythonScript(GameServer &gameServer, std::string fullFilePath);

            /**
             * @brief ~PythonScript virtual destructor -- Ćalled on Script::~Script.
             */
            virtual ~PythonScript();

            /**
             * @brief Load is a method to load and initalize the script.
             * @return true on success, false otherwise.
             */
            virtual bool Load() override;

            /**
             * @brief Unload is a method, that unloads all resources of a script.
             * @return true on success, false otherwise.
             */
            bool Unload() override;

            /**
             * @brief LoadIncludeScripts appends include script code to python code
             * @param pythonCode python code to search for includes and append code.
             */
            void LoadIncludeScripts(std::string &pythonCode);

            /**
             * @brief InvokePre switchs the thread state of the python interpreter for this script.
             */
            virtual void InvokePre() override;

            /**
             * @brief InvokePost switchs the thread state of the python interpreter back to main.
             */
            virtual void InvokePost() override;

        private:
            PyObject *m_pyObject;   //!< Python object to work with.
            PyObject *m_pyDict;     //!< Python dict.
            FILE *m_file;           //!< File pointer to read the script code from.
            PyThreadState* _main;   //!< Main thread state
            PyThreadState* ts;      //!< Isolated thread state
            static bool singleSetup;//!< Setup python library once only.
        };
    }
}
