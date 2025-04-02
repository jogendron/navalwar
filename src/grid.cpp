#include "grid.hpp"

Grid::Grid(const Engine::Position & position)
:   _position (position), 
    _gridImage (std::make_unique<Engine::Image>(Engine::Image("grid.png", position)))
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            _cells[i][j].setPosition(i+1, j+1, _position);
}

Grid::~Grid()
{
}

void Grid::draw()
{
    _gridImage->draw();
    
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            _cells[i][j].draw();
}