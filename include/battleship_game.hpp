#ifndef __BATTLESHIP_BATTLESHIP_GAME_HPP
#define __BATTLESHIP_BATTLESHIP_GAME_HPP

#include "engine/game.hpp"
#include "grid.hpp"

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

        void update();
        void render();

    private:
        BattleshipGameState _state;
        std::unique_ptr<Engine::Image> _background;
        std::unique_ptr<Grid> _playerGrid;
        std::unique_ptr<Grid> _enemyGrid;
};

#endif