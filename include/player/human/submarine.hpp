#ifndef __BATTLESHIP_PLAYER_HUMAN_SUBMARINE_HPP
#define __BATTLESHIP_PLAYER_HUMAN_SUBMARINE_HPP

#include "ship.hpp"

namespace Player::Human
{
    class Submarine : public Ship
    {
        public:
            Submarine(const Engine::Position & position);
            ~Submarine();
        
        private:
    };
}

#endif
