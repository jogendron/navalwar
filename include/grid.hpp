#ifndef __BATTLESHIP_GRID_HPP
#define __BATTLESHIP_GRID_HPP

#include <array>
#include <memory>

#include "engine/entity.hpp"
#include "engine/image.hpp"
#include "cell.hpp"

class Grid : public Engine::Entity
{
    public:
        Grid(const Engine::Position & position);
        ~Grid();

        void draw();

    private:
        Engine::Position _position;
        std::unique_ptr<Engine::Image> _gridImage;
        std::array<std::array<Cell, 10>, 10> _cells;
};

#endif