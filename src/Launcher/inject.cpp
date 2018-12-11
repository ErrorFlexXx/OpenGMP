#include "inject.h"
#include <Shared/Utils/logger.hpp>
#include <fstream>
#include <filesystem>
#include <vector>

using namespace std;

Inject::Inject()
    : startProgramSet(false)
    , parameters("")
    , injectProgramSet(false)
    , running(false)
{}

bool Inject::SetStartProgram(const std::string &startProgramFullPath,
                             const std::string &parameters)
{
    this->parameters = parameters;
    return GetFile(startProgramSet, startProgramFullPath, startProgram);
}

bool Inject::SetInjectProgram(const std::string &injectProgramFullPath)
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
    ResumeThread(pi.hThread);
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
    string strFullpath = injectProgram.string();

    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pi.dwProcessId);
    if(process == nullptr)
    {
        LogWarn() << "Process cannot be opened!";
        return false;
    }
    LPVOID pLoadLibrary = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"));
    if(pLoadLibrary == nullptr)
    {
        LogWarn() << "Cannot inject library! LoadLibraryA function not found!";
        return false;
    }
    LPVOID pRemoteLibPath = reinterpret_cast<LPVOID>(VirtualAllocEx(pi.hProcess, nullptr, strFullpath.length() + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    if(pRemoteLibPath == nullptr)
    {
        LogWarn() << "Cannot get memory inside the remote process";
        return false;
    }
    int n = WriteProcessMemory(pi.hProcess, pRemoteLibPath, strFullpath.c_str(), strFullpath.length(), nullptr);
    if(n == 0)
    {
        LogWarn() << "Write to remote process failed!";
        return false;
    }
    HANDLE hThread = CreateRemoteThread(pi.hProcess, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(pLoadLibrary), pRemoteLibPath, 0, nullptr);
    if(hThread == nullptr)
    {
        LogWarn() << "Creation of remote thread LoadLibraryA failed! Error Code: " << GetLastError();
        return false;
    }

    return true;
}

bool Inject::StartProcess()
{
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    //Prepare a non const wchar ptr for ms api.
    string strFullpath = startProgram.string();
    vector<char> fullpath(strFullpath.begin(), strFullpath.end());
    fullpath.push_back(0);

    if(!CreateProcessA(nullptr,
                      fullpath.data(),
                      nullptr,
                      nullptr,
                      FALSE,
                      CREATE_SUSPENDED,
                      nullptr,
                      nullptr,
                      &si,
                      &pi))
    {
        LogWarn() << "Create Process failed!";
        return false;
    }
    return true;
}

void Inject::AddEnvironmentVariable(
        pair<string, string> environmentVar)
{
    envVars.push_back(environmentVar); //Store in environment variables list.
}

void Inject::AppendEnvironmentVariable(
        pair<string, string> environmentVar)
{
    envAppendVars.push_back(environmentVar);
}

bool Inject::GetFile(bool &success, const string &filepath, experimental::filesystem::path &file)
{
    file.assign(filepath);

    ifstream test(file.string());
    if(!test.good())
    {
        LogWarn() << "The specified file " << file.string() << " cannot be opened!";
        success = false;
        return success;
    }

    return success = true;
}

bool Inject::SetupEnvironmentVariables()
{
    bool result = true;

    for(const auto &envPair : envVars) //For all registered variables
    {
        string set;
        set.append(envPair.first).append("=").append(envPair.second);
        result = (0 == _putenv(set.c_str()) && result);
    }

    for(const auto &appEnvPair : envAppendVars)
    {
        char *existing = nullptr;
        size_t sz = 0;

        string vars;
        vars.append(appEnvPair.second);
        if (_dupenv_s(&existing, &sz, appEnvPair.first.c_str()) == 0 && existing != nullptr)
        {
            vars.append(";");
            vars.append(existing);
            free(existing);
        }

        string set;
        set.append(appEnvPair.first).append("=").append(vars);
        result = (0 == _putenv(set.c_str()) && result);
    }

    return result;
}
