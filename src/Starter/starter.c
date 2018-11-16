#include "../Shared/Types/constants.hpp"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include <psapi.h>
#include <stdlib.h> //putenv

#define EXECPATHMAXLENGTH 1024

using namespace std;
using namespace OpenGMP;

string openGMPLibName = "OpenGMP.dll";
string serverAddress = "192.168.1.201";
unsigned short serverPort = 1760;

bool setConnectDataEnvVars()
{
	string hostEnvVar = hostnameEnvVarName;
	string portEnvVar = portEnvVarName;

	hostEnvVar += "=";
	hostEnvVar += serverAddress;
	portEnvVar += "=";
	portEnvVar += to_string(serverPort);

	putenv(hostEnvVar.c_str());
	putenv(portEnvVar.c_str());

	return true;
}

bool injectDll(PROCESS_INFORMATION *pi, const char *dllPath)
{
	DWORD procID = pi->dwProcessId;
	HANDLE hThread = pi->hThread;

	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	if(process == NULL) {
		printf("Error: the specified process couldn't be found.\n");
		return false;
	}
	
	/*
	* Get address of the LoadLibrary function.
	*/
	LPVOID addr = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	if(addr == NULL) {
		printf("Error: the LoadLibraryA function was not found inside kernel32.dll library.\n");
		return false;
	}
	
	/*
	* Allocate new memory region inside the process's address space.
	*/
	LPVOID arg = (LPVOID)VirtualAllocEx(process, NULL, strlen(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if(arg == NULL) {
		printf("Error: the memory could not be allocated inside the chosen process.\n");
		return false;
	}
	
	/*
	* Write the argument to LoadLibraryA to the process's newly allocated memory region.
	*/
	int n = WriteProcessMemory(process, arg, dllPath, strlen(dllPath), NULL);
	if(n == 0) {
		printf("Error: there was no bytes written to the process's address space.\n");
		return false;	
	}
	
	/*
	* Inject our DLL into the process's address space.
	*/
	HANDLE threadID = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)addr, arg, NULL, NULL);
	if(threadID == NULL) {
		printf("Error: the remote thread could not be created.\n");
		return false;
	}
	else {
		printf("Success: the remote thread was successfully created.\n");
	}
	
	ResumeThread(hThread);
	CloseHandle(process);
	return true;
}

int main(int argc, char **argv)
{
	char startProgram[] = "Gothic2.exe -zwindow";
	char injectDllName[] = "OpenGMP.dll";
	char executablePath[EXECPATHMAXLENGTH];
	string executionPath;
	stringstream parser;
	char *cstartFullpath;
	char *cinjectDllFullpath;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	//Clear memory first (GetModuleFileName delivers a non null terminated string..)
	ZeroMemory(executablePath, EXECPATHMAXLENGTH);
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	//Get executables path (without filename)
	GetModuleFileName(NULL, executablePath, EXECPATHMAXLENGTH-1);
	string::size_type pos = string(executablePath).find_last_of( "\\/" );
	executionPath = string(executablePath).substr( 0, pos + 1);

	//Assemble process start path
	parser << executionPath << startProgram;
	//Convert stringstream to string to cstring to char* (the dark side of c)
	cstartFullpath = new char[parser.str().length() + 1];
	strcpy(cstartFullpath, parser.str().c_str());
	parser.str(string("")); //Clear parser
	parser.clear();		//Clear parsers error flags

	//Assemble load dlls path
	parser << executionPath << injectDllName;
	cinjectDllFullpath = new char[parser.str().length() + 1];
	strcpy(cinjectDllFullpath, parser.str().c_str());
	parser.str(string("")); //Clear parser
	parser.clear();		//Clear parsers error flags

	setConnectDataEnvVars(); //Set connect data environment variables.

	// Start the child process.
	if( !CreateProcess( 
		NULL,   // No module name (use command line)
		cstartFullpath,	// Command line
		NULL,		// Process handle not inheritable
		NULL,		// Thread handle not inheritable
		FALSE,		// Set handle inheritance to FALSE
		CREATE_SUSPENDED,		// No creation flags
		NULL,		// Use parent's environment block
		NULL,		// Use parent's starting directory 
		&si,		// Pointer to STARTUPINFO structure
		&pi))		// Pointer to PROCESS_INFORMATION structure
	{
		printf( "CreateProcess failed (%d).\n", (int)GetLastError() );
		return 1;
	}

	DWORD result = WaitForInputIdle(pi.hProcess, 5000);

	injectDll(&pi, cinjectDllFullpath);

	// Wait until child process exits.
	WaitForSingleObject( pi.hProcess, INFINITE );

	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	return 0;
}
