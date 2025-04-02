#ifndef __BATTLESHIP_CELL_HPP
#define __BATTLESHIP_CELL_HPP

#include "engine/entity.hpp"
#include "engine/position.hpp"

enum CellState
{
    INITIAL,
    TOUCHED,
    MISSED
};

class Cell : public Engine::Entity
{
    public:
        Cell();
        ~Cell();

        void setState(const CellState& state);
        void setPosition(int row, int line, const Engine::Position& gridPosition);

        void draw();

    private:
        CellState _state;
        SDL_FRect _rect;
};

#endif