#pragma once

#include <Client/Types/virtualKeys.hpp>
#include <Client/Components/menuMain.hpp>
#include <Client/Components/menuRegister.hpp>
#include <Client/Components/notificationBox.hpp>
#include <Shared/Components/color.hpp>
#include <list>

//Forward declarations:
namespace RakNet
{
    struct Packet;
}

namespace OpenGMP
{
    class GameClient;

    namespace GUI
    {
        class Menu;
    }

    namespace Systems
    {
        class MenuSystem
        {
        public:
            MenuSystem(GameClient &gameClient);
            
            void CloseActiveMenus();
            bool IsMenuActive();
            bool KeyDownUpdateMenus(Types::VirtualKeys key);
            bool KeyUpUpdateMenus(Types::VirtualKeys key);
            void UpdateMenus(unsigned long long now);
            void UpdateNotification(unsigned long long now);
            void ShowNotification(int posY, std::string &text, Components::Color &color, uint32_t durationMS = 0);
            void HideNotification();
            void Process(RakNet::Packet *packet);

            Components::MenuMain menuMain;
            Components::MenuRegister menuRegister;
            Components::NotificationBox notification;

        private:
            GameClient &gameClient;
        };
    }
}