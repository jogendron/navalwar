#ifndef __NAVALWAR_PLAYER_HUMAN_GRID_HPP
#define __NAVALWAR_PLAYER_HUMAN_GRID_HPP

#include "player/grid.hpp"
#include "player/human/ship.hpp"

namespace Player::Human
{
    class HumanGrid : public Grid
    {
        public:
            HumanGrid(const Engine::Position & position);
            ~HumanGrid();

            void snap(Ship & ship);

        private:
    };
}

#endif