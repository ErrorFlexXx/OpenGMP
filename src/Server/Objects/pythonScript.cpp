#include "pythonScript.hpp"
#include <utils/logger.h>

using namespace std;
using namespace cpgf;
using namespace OpenGMP::Objects;

PythonScript::PythonScript(std::string filename)
    : Script(filename)
{
}

PythonScript::~PythonScript()
{
}

bool PythonScript::Load()
{
    Py_Initialize();
    string pythonCode;
    if(!ReadStringFromFile(m_filename, &pythonCode))
    {
        LogError() << "Read failed for python script file: " << m_filename.c_str();
        return false;
    }
    PyRun_SimpleString(pythonCode.c_str());
    m_pyObject = PyImport_ImportModule("__main__");
    m_pyDict = PyModule_GetDict(m_pyObject);
    Py_XINCREF(m_pyDict);
    m_service = new GScopedInterface<IMetaService>(createDefaultMetaService());
    m_binding = new GScopedPointer<GScriptObject>(createPythonScriptObject(m_service->get(), m_pyObject));
    m_scope = new GScopedInterface<IScriptObject>(m_binding->get()->createScriptObject("OpenGMP").toScriptObject());

    LoadClasses();
    LoadGlobals();

    return true;
}

bool PythonScript::Unload()
{
    Py_XDECREF(m_pyDict);
    Py_XDECREF(m_pyObject);
    Py_Finalize();
    return true;
}
