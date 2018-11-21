#pragma once

#include <list>
#include <string>
#include <tinydir/tinydir.h>
#include <windows.h>
#include <stdlib.h> //putenv

/**
 * @brief The Inject class
 * @author Christian Löpke <loepke@edfritsch.de>
 *   Class used to start a program and inject another program in it on windows.
 */
class Inject
{
public:
    /**
     * @brief SetStartProgram sets the path to the program, that shall be started.
     * @param startProgramFullPath the full path to the executable file.
     * @return true, if the file was found, false otherwise.
     */
    bool SetStartProgram(const std::wstring &startProgramFullPath, const std::wstring &parameters);

    /**
     * @brief SetInjectProgram sets the path to the library, that shall be injected.
     * @param injectProgramFullPath full path to the library file.
     * @return true, if the file was found, false otherwise.
     */
    bool SetInjectProgram(const std::wstring &injectProgramFullPath);

    /**
     * @brief Start starts the program and injection.
     * @param blocking on true the call will return, if the started program ends.
     * @return true, if the program start and injection was successfull, false otherwise.
     */
    bool Start(bool blocking = false);

    /**
     * @brief Stop stops a running program, if any.
     * @return true, if a program was stopped.
     */
    bool Stop();

    /**
     * @brief AddEnvironmentVariable adds an environment variable, the started program will inherit.
     * @param environmentVar pair of strings (key=value).
     */
    void AddEnvironmentVariable(std::pair<std::string, std::string> environmentVar);

protected:
    /**
     * @brief GetFile gets file informations and sets a successflag.
     * @param success (out) set to true, if file could be found.
     * @param filepath full filepath to the file, which shall be opened.
     * @param file (out) the file object to store the informations in.
     * @return true, if file was found, false otherwise.
     */
    bool GetFile(bool &success, const std::wstring &filepath, tinydir_file &file);

    /**
     * @brief SetupEnvironmentVariables sets all registered environment variables for this process.
     *   Environment variables will be inherited by a started process.
     * @return true, if environment variables has been set, false otherwise.
     */
    bool SetupEnvironmentVariables();

    /**
     * @brief StartProcess starts the actual process.
     * @return true, if the process was started, false otherwise.
     */
    bool StartProcess();

    /**
     * @brief DoInjection does the actual injection.
     * @return true, if the library was injected successfully.
     */
    bool DoInjection();

private:
    bool startProgramSet;       //!< Reminder, if a start program has been set.
    tinydir_file startProgram;  //!< Program that shall be started
    std::wstring parameters;     //!< Parameters, passed to startProgram on start.
    bool injectProgramSet;      //!< Reminder, if an inject program has been set.
    tinydir_file injectProgram; //!< Program that is injected into started program.
    std::list<std::pair<std::string, std::string>> environmentVariables; //!< List of environment variable key pairs.
    bool running;           //!< Running flag of started process.
    STARTUPINFO si;         //!< StartupInfo structure for CreateProcess.
    PROCESS_INFORMATION pi; //!< ProcessInformation for CreateProcess.
};
