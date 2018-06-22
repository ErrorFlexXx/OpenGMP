#pragma once

#include "../hook.hpp"
#include <Client/Gothic/Types/zCOLOR.hpp>
#include "../Menus/ogmpMainMenu.hpp"

namespace OpenGMP
{
    namespace Hooks
    {
        class HGame
        {
        public:
            static HGame *GetInstance();
            void DoHook();
            void UndoHook();

        private:
            /**
             * @brief private contructor for singleton instance creation.
             */
            HGame();

            /**
            * @brief private copy contructor -- copy forbidden for singleton.
            */
            HGame(HGame &cpy);

            static HGame *instance; //!< Singleton instance of HGame.
            Hook m_hookOutgame;     //!< Outgame hook (menus).
            Hook m_hookIngame;      //!< Outgame hook (game rendering).
            static bool outgameStarted; //!< Flag to create initial outgame
            static OpenGMP::Menus::OGMPMainMenu *mainMenu; //!< Main menu
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
            static void StartOutgame();
        };
    }
}