#ifndef __NAVALWAR_PLAYER_GRID_HPP
#define __NAVALWAR_PLAYER_GRID_HPP

#include <array>
#include <memory>
#include <string>

#include "engine/entity.hpp"
#include "engine/image.hpp"
#include "player/cell.hpp"

namespace Player
{
    class Grid : public Engine::Entity
    {
        public:
            Grid(const Engine::Position & position);
            ~Grid();

            Cell & getCell(const std::string & positionName);
            Cell * getClickedCell(float x, float y);

            void draw();
            
        protected:
            Engine::Position _position;
            std::unique_ptr<Engine::Image> _gridImage;
            std::array<std::array<Cell, 10>, 10> _cells;
    };
}

#endif
