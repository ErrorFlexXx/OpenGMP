#include "inject.h"
#include <tinydir/tinydir.h>
#include <ZenLib/utils/logger.h>

using namespace std;

Inject::Inject()
    : startProgramSet(false)
    , injectProgramSet(false)
    , parameters("")
    , running(false)
{}

bool Inject::SetStartProgram(const std::wstring &startProgramFullPath,
                             const std::wstring &parameters)
{
    this->parameters = parameters;
    return GetFile(startProgramSet, startProgramFullPath, startProgram);
}

bool Inject::SetInjectProgram(const std::wstring &injectProgramFullPath)
{
    return GetFile(injectProgramSet, injectProgramFullPath, injectProgram);
}

bool Inject::Start(bool blocking)
{
    if(!startProgramSet)
    {
        LogWarn() << "Start program not set! Run SetStartProgram first!";
        return false;
    }
    if(!injectProgramSet)
    {
        LogWarn() << "Inject program not set! Run SetInjectProgram first!";
        return false;
    }
    if(!SetupEnvironmentVariables())
    {
        LogWarn() << "Environment variables setup failed!";
        return false;
    }
    if(!StartProcess())
    {
        LogWarn() << "Process cannot be started!";
        return false;
    }
    if(!DoInjection())
    {
        LogWarn() << "Injection failed!";
        return false;
    }
    if(blocking)
    {
        ResumeThread(pi.hThread);
        running = true;
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        return true;
    }
    //Non blocking:
    running = true;
    ResumeThread(pi.hProcess);
    return true;
}

bool Inject::Stop()
{
    if(running)
    {
        TerminateProcess(pi.hProcess, 0);
        running = false;
        return true;
    }
    return false;
}

bool Inject::DoInjection()
{
    wstring libraryFullpath;
    libraryFullpath.append(injectProgram.path);
    libraryFullpath.append(L"/");
    libraryFullpath.append(injectProgram.name);
    libraryFullpath.append(L".");
    libraryFullpath.append(injectProgram.extension);

    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pi.dwProcessId);
    if(process == NULL)
    {
        LogWarn() << "Process cannot be opened!";
        return false;
    }
    LPVOID pLoadLibrary = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryW");
    if(pLoadLibrary == NULL)
    {
        LogWarn() << "Cannot inject library! LoadLibraryA function not found!";
        return false;
    }
    LPVOID pRemoteLibPath = (LPVOID)VirtualAllocEx(pi.hProcess, NULL, libraryFullpath.length() + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if(pRemoteLibPath == NULL)
    {
        LogWarn() << "Cannot get memory inside the remote process";
        return false;
    }
    int n = WriteProcessMemory(pi.hProcess, pRemoteLibPath, libraryFullpath, libraryFullpath.length(), NULL);
    if(n == 0)
    {
        LogWarn() << "Write to remote process failed!";
        return false;
    }
    HANDLE hThread = CreateRemoteThread(pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE) pLoadLibrary, pRemoteLibPath, NULL, NULL);
    if(hThread)
    {
        LogWarn() << "Creation of remote thread LoadLibraryA failed!";
        return false;
    }

    return true;
}

bool Inject::StartProcess()
{
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    wstring startProgramFullpath;
    startProgramFullpath.append(startProgram.path);
    startProgramFullpath.append(L"/");
    startProgramFullpath.append(startProgram.name);
    startProgramFullpath.append(L".");
    startProgramFullpath.append(startProgram.extension);

    if(!CreateProcess(NULL,
                      startProgramFullpath.c_str(),
                      NULL,
                      NULL,
                      FALSE,
                      CREATE_SUSPENDED,
                      NULL,
                      NULL,
                      &si,
                      &pi))
    {
        LogWarn() << "Create Process failed!";
        return false;
    }

    if(0 != WaitForInputIdle(pi.hProcess, 5000)) //Wait till process loading is finished.
    {
        LogWarn() << "Process setup failed (Timeout).";
        return false;
    }
    return true;
}

void Inject::AddEnvironmentVariable(
        std::pair<std::string, std::string> environmentVar)
{
    environmentVariables.push_back(environmentVar); //Store in environment variables list.
}

bool Inject::GetFile(bool &success, const std::wstring &filepath, tinydir_file &file)
{
    if(-1 == tinydir_file_open(&file, filepath.c_str()))
    {
        LogWarn() << "The specified file cannot be found!";
        success = false;
        return success;
    }

    return success;
}

bool Inject::SetupEnvironmentVariables()
{
    int result = true;

    for(const auto &envPair : environmentVariables) //For all registered variables
    {
        string set;
        set.append(envPair.first).append("=").append(envPair.second);
        result = (0 == _putenv(set.c_str()) && result);
    }

    return result;
}
