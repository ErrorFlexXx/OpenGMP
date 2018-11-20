#include "inject.h"
#include <tinydir/tinydir.h>
#include <ZenLib/utils/logger.h>

using namespace std;

Inject::Inject()
    : startProgramSet(false)
    , injectProgramSet(false)
    , parameters("")
{}

bool Inject::SetStartProgram(const std::string &startProgramFullPath,
                             const std::string &parameters)
{
    return GetFile(startProgramSet, startProgramFullPath, startProgram);
}

bool Inject::SetInjectProgram(const std::string &injectProgramFullPath)
{
    return GetFile(injectProgramSet, injectProgramFullPath, injectProgram);
}

bool Inject::Start(bool blocking = false)
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


}

bool Inject::Stop()
{

}

void Inject::AddEnvironmentVariable(
        std::pair<std::string, std::string> environmentVar)
{
    environmentVariables.push_back(environmentVar); //Store in environment variables list.
}

bool Inject::GetFile(bool &success, const std::string &filepath, tinydir_file &file)
{
    if(-1 == tinydir_file_open(&file, filepath.c_str()))
    {
        LogWarn() << "File " << filepath << " cannot be found!";
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
        result = (0 == putenv(set.c_str()) && result);
    }

    return result;
}
