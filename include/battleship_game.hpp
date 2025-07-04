#ifndef __BATTLESHIP_BATTLESHIP_GAME_HPP
#define __BATTLESHIP_BATTLESHIP_GAME_HPP

#include <array>
#include <functional>
#include <memory>

#include "engine/game.hpp"
#include "grid.hpp"
#include "carrier.hpp"
#include "battleship.hpp"
#include "cruiser.hpp"
#include "submarine.hpp"
#include "destroyer.hpp"
#include "start_button.hpp"

enum BattleshipGameState
{
    PRE_GAME,
    GAMING,
    POST_GAME
};

class BattleshipGame : public Engine::Game
{
    public:
        BattleshipGame();
        ~BattleshipGame();

        void processEvent(const SDL_Event & event);
        void update();
        void render();

    private:
        BattleshipGameState _state;
        std::unique_ptr<Engine::Image> _background;
        std::unique_ptr<Grid> _playerGrid;
        std::unique_ptr<Grid> _enemyGrid;
        std::array<std::unique_ptr<Ship>, 5> _ships;
        std::unique_ptr<StartButton> _startButton;

        void processShipEvent(const SDL_Event & event);
        void processStartButtonEvent(const SDL_Event & event);

        void updateShips();
        void updateStartButton();

        bool allShipsOnGrid() const;
        void startGame();
};

#endif