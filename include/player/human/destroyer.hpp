#ifndef __BATTLESHIP_PLAYER_HUMAN_DESTROYER_HPP
#define __BATTLESHIP_PLAYER_HUMAN_DESTROYER_HPP

#include "ship.hpp"

namespace Player::Human
{
    class Destroyer : public Ship
    {
        public:
            Destroyer(const Engine::Position & position);
            ~Destroyer();
            
        private:
    };
}

#endif
