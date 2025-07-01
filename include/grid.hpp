#ifndef __BATTLESHIP_GRID_HPP
#define __BATTLESHIP_GRID_HPP

#include <array>
#include <memory>
#include <string>

#include "engine/entity.hpp"
#include "engine/image.hpp"
#include "cell.hpp"
#include "ship.hpp"

class Grid : public Engine::Entity
{
    public:
        Grid(const Engine::Position & position);
        ~Grid();

        Cell & getCell(const std::string & positionName);

        void snap(Ship & ship) const;
        void draw();
        
    private:
        Engine::Position _position;
        std::unique_ptr<Engine::Image> _gridImage;
        std::array<std::array<Cell, 10>, 10> _cells;
};

#endif