#include "terminalSystem.hpp"
#include "../gameServer.hpp"
#include <utils/logger.h>
#ifndef WIN32
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#else
#pragma warning "Non blocking read implementation for windows missing!"
#endif

using namespace std;
using namespace OpenGMP;

#ifndef WIN32
struct termios orig_termios;

void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}
#endif

TerminalSystem::TerminalSystem(GameServer &gameServer)
    : gameServer(gameServer)
    , commandReady(false)
{}

bool TerminalSystem::Startup()
{
    return true;
}

bool TerminalSystem::Update()
{
    bool idle = true;
#ifndef WIN32
    if(kbhit())
    {
        idle = false;
        int character = getch();
        if(character == 0xa) //Enter ?
            commandReady = true;
        else
            inputLine.push_back((char)character);
//        LogInfo() << "0x" << hex << character << " ";
    }

    if(commandReady)
    {
        idle = false;
        bool found = false;
        if(actions.find(inputLine) != actions.end())
        {
            found = true;
            actions[inputLine]();
        }
        if(found == false)
            LogInfo() << "Unknown command: " << inputLine << "! Try \"help\" to get a command list.";
        inputLine.clear();
        commandReady = false;
    }
#endif
    return !idle; //Return if we have done something.
}

void TerminalSystem::Shutdown()
{
}

void TerminalSystem::AddCommand(const string &command,
                                const string &description,
                                const function<void ()> action)
{
    actions[command] = action;
    descriptions[command] = description;
}

string TerminalSystem::GetDescription(const string &command)
{
    if(descriptions.find(command) != descriptions.end())
    {
        return descriptions[command];
    }
    return string("Unknown command");
}

void TerminalSystem::GetHelp()
{
    LogInfo() << "Registered commands:";
    for( auto &help : descriptions )
    {
        LogInfo() << help.first << " | " << help.second;
    }
}
