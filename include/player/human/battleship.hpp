#ifndef __NAVALWAR_PLAYER_HUMAN_BATTLESHIP_HPP
#define __NAVALWAR_PLAYER_HUMAN_BATTLESHIP_HPP

#include "ship.hpp"

namespace Player::Human
{
    class Battleship : public Ship
    {
        public:
            Battleship(const Engine::Position & position);
            ~Battleship();

        private:
    };
}

#endif
