#pragma once

#include "../Types/virtualKeys.hpp"
#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include <functional>
#include <list>
#include <map>

#define KEYCOUNT 255

namespace OpenGMP
{
    class GameClient;

    class InputSystemKeyDownRepeat
    {
    public:
        InputSystemKeyDownRepeat(GameClient &gameClient, std::function<void(VirtualKeys)> action, int holdTime = 600, int rate = 75);

        int holdTime;
        int rate;
        void Update(unsigned long long now);
        void KeyDown(const VirtualKeys &key, unsigned long long now);

    private:
        GameClient &gameClient;
        unsigned long long nextTime;
        VirtualKeys currentKey;
        std::function<void(VirtualKeys)> action;
    };

    struct ActionKeyCombinationBinding
    {
        ActionKeyCombinationBinding(
            const std::list<VirtualKeys> &keyCombination,
            const std::function<void()> &action)
            : keyCombination(keyCombination)
            , action(action) {}

        std::list<VirtualKeys> keyCombination;
        std::function<void()> action;
    };

    class InputSystemKeyCombination
    {
    public:
        InputSystemKeyCombination(GameClient &gameClient, int holdTime = 600, int rate = 150);

        int holdTime;
        int rate;
        void Add(const std::list<VirtualKeys> &keyCombination, const std::function<void()> &action);
        void Update(unsigned long long now);

    private:
        GameClient &gameClient;
        std::list <ActionKeyCombinationBinding*> actionKeyCombinationBindings;
        unsigned long long nextTime;
        ActionKeyCombinationBinding *current;
    };

    class InputSystem
    {
    public:
        InputSystem(GameClient &gameClient);
        void Update();
        std::function<void(VirtualKeys key)> keyDownReceipient;
        std::function<void(VirtualKeys key)> keyUpReceipient;
        bool mouseShown;
        int movedX;
        int movedY;
        int MouseDistX();
        int MouseDistY();
        POINT oriPos;
        const int defaultMousePosX;
        const int defaultMousePosY;
        bool m_shown;
        bool IsPressed(VirtualKeys key);

    private:
        GameClient &gameClient;
        bool m_keys[KEYCOUNT];
    };
}
