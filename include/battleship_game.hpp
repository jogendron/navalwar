#ifndef __BATTLESHIP_BATTLESHIP_GAME_HPP
#define __BATTLESHIP_BATTLESHIP_GAME_HPP

#include "engine/game.hpp"

class BattleshipGame : public Engine::Game
{
    public:
        BattleshipGame();
        ~BattleshipGame();

        void update();
        void render();

    private:
        std::unique_ptr<Engine::Image> _background;
};

#endif