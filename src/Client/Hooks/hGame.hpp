#pragma once

#include <Client/Objects/CDetour.h>
#include <Client/Gothic/Types/zCOLOR.hpp>

namespace OpenGMP
{
    class GameClient;

    class HGame
    {
    public:
        HGame();
        HGame(GameClient &gameClient);

        void Startup();
        void Shutdown();

        /**
         * @brief StartOutgame - Does setup tasks to create outgame resources.
         */
        void StartOutgame();

        bool outgameStarted; //!< Flag to create initial outgame
        bool gameStarted; //!< Flag to remember if a game was started
        zCOLOR blankColor;

    private:
        /**
         * @brief private copy contructor -- copy forbidden.
         */
        HGame(HGame &cpy);

        GameClient &gameClient;

        CDetour *menuDetour;     //!< Detour of CGameManager::Menu
        CDetour *renderDetour;   //!< Detour of oCGame::Render
    };
}