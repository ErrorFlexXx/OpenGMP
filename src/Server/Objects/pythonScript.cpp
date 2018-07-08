#include "pythonScript.hpp"
#include "../gameServer.hpp"
#include <utils/logger.h>
#include <regex>

using namespace std;
using namespace cpgf;
using namespace OpenGMP;
using namespace OpenGMP::Objects;

bool PythonScript::singleSetup = false;

PythonScript::PythonScript(GameServer &gameServer, std::string filename)
    : Script(gameServer, filename)
{
}

PythonScript::~PythonScript()
{
}

bool PythonScript::Load()
{
    if(PythonScript::singleSetup == false)
    {
        PythonScript::singleSetup = true;
        Py_Initialize();
        PyEval_InitThreads();
    }

    PyThreadState* _main = PyThreadState_Get(); //Get Main thread state
    ts = Py_NewInterpreter(); //Create dedicated thread state for this script
    PyThreadState_Swap(ts); //Set new thread state

    string pythonCode;
    if(!ReadStringFromFile(m_fullFilePath, &pythonCode))
    {
        LogError() << "Read failed for python script file: " << m_fullFilePath.c_str();
        return false;
    }

    LoadIncludeScripts(pythonCode); //Load included scripts in this python thread state

    string setPath = string("import sys\nsys.path.append('").append(m_gameServer.scriptDirectory).append("')\n");
    PyRun_SimpleString(
       setPath.c_str()
    );
    PyRun_SimpleString(pythonCode.c_str());
    m_pyObject = PyImport_ImportModule("__main__");
    m_pyDict = PyModule_GetDict(m_pyObject);
    Py_XINCREF(m_pyDict);
    m_service = new GScopedInterface<IMetaService>(createDefaultMetaService());
    m_binding = new GScopedPointer<GScriptObject>(createPythonScriptObject(m_service->get(), m_pyObject));
    m_scope = new GScopedInterface<IScriptObject>(m_binding->get()->createScriptObject("OpenGMP").toScriptObject());

    LoadClasses();
    LoadGlobals();

    PyThreadState_Swap(_main); //Reset main thread state.

    return true;
}

bool PythonScript::Unload()
{
    Py_XDECREF(m_pyDict);
    Py_XDECREF(m_pyObject);

    PyThreadState* _main = PyThreadState_Get(); //Get Main interpreter
    PyThreadState_Swap(NULL);
    PyThreadState_Clear(ts);
    PyThreadState_Delete(ts);
    PyThreadState_Swap(_main);

    //Py_Finalize();
    return true;
}

void PythonScript::LoadIncludeScripts(string &pythonCode)
{
    regex exp("(?:\#include)(?:\ )?[\<\"](.*)[\"\>]");
    smatch res;
    list<string> includes;
    string::const_iterator searchStart( pythonCode.cbegin() );
    while ( regex_search( searchStart, pythonCode.cend(), res, exp ) )
    {
        includes.push_back(res.str(1));
        searchStart += res.position() + res.length();
    }

    for(const string &include : includes) //Insert code on top
    {
        if(0 < include.size())
        {
            string incCode;
            string includeFilePath = string(m_gameServer.scriptDirectory).append(include);
            if(!ReadStringFromFile(includeFilePath, &incCode))
                LogWarn() << "Python #include directive cant load file: " << includeFilePath;
            else
            {
                incCode.append("\r\n");
                pythonCode.insert(0, incCode);
            }
        }
    }
}

void PythonScript::InvokePre()
{
    _main = PyThreadState_Get(); //Get Main interpreter
    PyThreadState_Swap(ts);
}

void PythonScript::InvokePost()
{
    PyThreadState_Swap(_main);
}
