#include "player/human/human_grid.hpp"

using namespace Player;
using namespace Player::Human;

HumanGrid::HumanGrid(const Engine::Position & position)
: Grid(position)
{
}

HumanGrid::~HumanGrid()
{
}

void HumanGrid::snap(Ship & ship)
{
    const Engine::Position & gridPosition = _gridImage->getPosition();
    const Engine::Dimensions & gridDimensions = _gridImage->getDimensions();

    const Engine::Position & shipPosition = ship.getPosition();
    const Player::Human::ShipOrientation shipOrientation = ship.getOrientation();
    const Engine::Dimensions & shipDimensions = ship.getDimensions();

    const Engine::Dimensions & cellDimensions = _cells[0][0].getDimensions();

    int shipWidth = shipDimensions.getWidth();
    int shipHeight = shipDimensions.getHeight();

    if (shipOrientation == Player::Human::ShipOrientation::VERTICAL)
        std::swap(shipWidth, shipHeight);

    if (
        shipPosition.getX() >= gridPosition.getX()
        && (shipPosition.getX() + shipWidth) <= (gridPosition.getX() + gridDimensions.getWidth() + cellDimensions.getWidth() / 3)
        && shipPosition.getY() >= gridPosition.getY()
        && (shipPosition.getY() + shipHeight) <= (gridPosition.getY() + gridDimensions.getHeight() + cellDimensions.getHeight() / 3)
    )
    {
        float x = 0;
        int rowIndex = 0;
        float y = 0;
        int columnIndex = 0;
        
        for (int i = 0; i < 10 && (x == 0 || y == 0); i++)
        {
            if (x == 0)
            {                
                const Engine::Position & cellPosition = _cells[0][i].getPosition();
                float xCoverage = std::max(cellPosition.getX() + cellDimensions.getWidth() - shipPosition.getX(), 0.0f) / cellDimensions.getWidth() * 100;
             
                if (xCoverage >= 50)
                {
                    x = cellPosition.getX();                       
                    columnIndex = i;
                }
            }

            if (y == 0)
            {
                const Engine::Position & cellPosition = _cells[i][0].getPosition();
                float yCoverage = std::max(cellPosition.getY() + cellDimensions.getHeight() - shipPosition.getY(), 0.0f) / cellDimensions.getHeight() * 100;
             
                if (yCoverage >= 50)
                {
                    y = cellPosition.getY();   
                    rowIndex = i;
                }
            }
        }

        if (x > 0 && y > 0)
        {
            std::vector<std::reference_wrapper<Cell>> overlappingCells;
            int overlappedCellRowIndex = rowIndex;
            int overlappedCellColumnIndex = columnIndex;
            int overlappingCellsCount = std::max(shipWidth, shipHeight) / cellDimensions.getWidth();

            overlappingCells.push_back(std::ref(_cells[overlappedCellRowIndex][overlappedCellColumnIndex]));
            for (int i = 1; i < overlappingCellsCount; i++)
            {
                if (shipOrientation == Player::Human::ShipOrientation::HORIZONTAL)
                    overlappedCellColumnIndex++;
                else
                    overlappedCellRowIndex++;

                overlappingCells.push_back(
                    std::ref(_cells[overlappedCellRowIndex][overlappedCellColumnIndex])
                );
            }

            ship.snap(Engine::Position(x, y), overlappingCells);
        }
        else
            ship.failSnap();
    }
    else
    {
        ship.failSnap();
    }
}