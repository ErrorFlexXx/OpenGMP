#pragma once

#include "hook.hpp"
#include <Client/Gothic/Types/zCOLOR.hpp>

namespace OpenGMP
{
    class GameClient;

    namespace Hooks
    {
        class HGame
        {
        public:
            HGame(GameClient &gameClient);
            void Startup();
            void Shutdown();

            static HGame *instance; //!< Instance to get the object from (hooked) non member function.
        private:
            /**
            * @brief private copy contructor -- copy forbidden.
            */
            HGame(HGame &cpy);

            GameClient &gameClient;
            Hook m_hookOutgame;     //!< Outgame hook (menus).
            Hook m_hookIngame;      //!< Outgame hook (game rendering).
            static bool outgameStarted; //!< Flag to create initial outgame
            static zCOLOR blankColor;

            /**
             * @brief RunOutgame - To be hooked, to get hook on outgame rendering process.
             *  Outgame can be used for main menus for example. Not called on ingame rendering.
             */
            static void RunOutgame();

            /**
             * @brief RunIngame - To be hooked, to get hook on ingame rendering process.
             *  Ingame can be used for main game rendering.
             */
            static void RunIngame();

            /**
             * @brief StartOutgame - Does setup tasks to create outgame resources.
             */
            void StartOutgame();
        };
    }
}