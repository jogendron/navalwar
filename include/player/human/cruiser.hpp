#ifndef __BATTLESHIP_PLAYER_HUMAN_CRUISER_HPP
#define __BATTLESHIP_PLAYER_HUMAN_CRUISER_HPP

#include "ship.hpp"

namespace Player::Human
{
    class Cruiser : public Ship
    {
        public:
            Cruiser(const Engine::Position & position);
            ~Cruiser();
        
        private:
    };
}

#endif
