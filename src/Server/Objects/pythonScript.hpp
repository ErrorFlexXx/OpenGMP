#pragma once

#include <string>
#include <cpgf/scriptbind/gpythonrunner.h>
#include <cpgf/scriptbind/gpythonbind.h>

#include "script.hpp"

namespace OpenGMP
{
    namespace Objects
    {
        class PythonScript : public Script
        {
        public:
            /**
             * @brief PythonScript constructs a PythonScript object and loads the code.
             * @param filename of the python script file
             */
            PythonScript(std::string filename);

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

        private:
            PyObject *m_pyObject;   //!< Python object to work with.
            PyObject *m_pyDict;     //!< Python dict.
            FILE *m_file;           //!< File pointer to read the script code from.
        };
    }
}
