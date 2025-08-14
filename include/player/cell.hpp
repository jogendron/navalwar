#ifndef __BATTLESHIP_PLAYER_CELL_HPP
#define __BATTLESHIP_PLAYER_CELL_HPP

#include "engine/dimensions.hpp"
#include "engine/entity.hpp"
#include "engine/position.hpp"

#include <string>

namespace Player
{
    enum CellState
    {
        INITIAL,
        HIT,
        MISSED
    };

    class Cell : public Engine::Entity
    {
        public:
            Cell();
            ~Cell();

            const std::string & getPositionName() const;
            const Engine::Position & getPosition() const;
            const Engine::Dimensions & getDimensions() const;
            const CellState getState() const;
            
            void setState(const CellState& state);
            void setPosition(int line, int row, const Engine::Position& gridPosition);

            void draw();

        private:
            std::string _positionName;
            Engine::Position _position;
            Engine::Dimensions _dimensions;
            CellState _state;
    };
}

#endif
