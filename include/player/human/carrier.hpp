#ifndef __BATTLESHIP_PLAYER_HUMAN_CARRIER_HPP
#define __BATTLESHIP_PLAYER_HUMAN_CARRIER_HPP

#include "ship.hpp"

namespace Player::Human
{
    class Carrier : public Ship
    {
        public:
            Carrier(const Engine::Position & position);
            ~Carrier();
        
        private:
    };
}

#endif
