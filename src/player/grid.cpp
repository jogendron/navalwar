#include <algorithm>
#include <vector>
#include "player/grid.hpp"

using namespace Player;

Grid::Grid(const Engine::Position & position)
:   _position (position), 
    _gridImage (std::make_unique<Engine::Image>(Engine::Image("grid.png", position)))
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            _cells[i][j].setPosition(i, j, _position);
}

Grid::~Grid()
{
}

Cell & Grid::getCell(const std::string & positionName)
{
    if (positionName.length() != 2 && positionName.length() != 3)
        throw std::invalid_argument("Position name must be two or three characters long.");

    char line = positionName[0];
    int lineIndex = line - 'A';
    int rowIndex = std::stoi(positionName.substr(1)) - 1;

    if (line < 'A' || line > 'J' || rowIndex < 0 || rowIndex > 9)
        throw std::out_of_range("Line must be between A and J, row must be between 0 and 9.");

    return _cells[lineIndex][rowIndex];
}

Cell * Grid::getClickedCell(float x, float y)
{
    Cell * clickedCell = nullptr;
    
    for (int i = 0; i < 10 && clickedCell == nullptr; i++)
    {
        for (int j = 0; j < 10 && clickedCell == nullptr; j++)
        {
            const Engine::Position & cellPosition = _cells[i][j].getPosition();
            const Engine::Dimensions & cellDimensions = _cells[i][j].getDimensions();

            if (
                x >= cellPosition.getX()
                && x <= (cellPosition.getX() + cellDimensions.getWidth())
                && y >= cellPosition.getY()
                && y <= (cellPosition.getY() + cellDimensions.getHeight())
            )
            {
                clickedCell = &_cells[i][j];
            }
        }
    }

    return clickedCell;
}

void Grid::draw()
{
    _gridImage->draw();
    
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            _cells[i][j].draw();
}
