#include "player/cell.hpp"
#include "engine/engine.hpp"

using namespace Player;

Cell::Cell()
:   _position (Engine::Position(0, 0)),
    _dimensions (Engine::Dimensions(0,0)),
    _state (CellState::INITIAL)
{
}

Cell::~Cell()
{
}

const std::string & Cell::getPositionName() const
{
    return _positionName;
}

const Engine::Position & Cell::getPosition() const
{
    return _position;
}
        
const Engine::Dimensions & Cell::getDimensions() const
{
    return _dimensions;
}

const CellState Cell::getState() const
{
    return _state;
}

void Cell::setState(const CellState& state)
{
    _state = state;
}

void Cell::setPosition(int line, int row, const Engine::Position& gridPosition)
{
    Engine::Engine& engine = Engine::Engine::getInstance();
    Engine::Resolution resolution = engine.getConfiguration()->getResolution();

    char lineNames[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    float firstCellX = 0;
    float firstCellY = 0;
    float lineWidth = 0;

    if (line < 0 || line > 9 || row < 0 || row > 9)
        throw std::out_of_range("Line and row must be between 0 and 9.");

    switch (resolution.getWidth())
    {
        case 1280:
            firstCellX = 50;
            firstCellY = 50;
            lineWidth = 1.35;

            _dimensions = Engine::Dimensions(48, 48);
            break;

        case 1920:
            firstCellX = 72;
            firstCellY = 72;
            lineWidth = 5;

            _dimensions = Engine::Dimensions(72, 72);
            break;

        case 3840:
            firstCellX = 144;
            firstCellY = 144;
            lineWidth = 10;

            _dimensions = Engine::Dimensions(144, 144);
            break;
    }

    _positionName = std::string(1, lineNames[line]) + std::to_string(row + 1);

    _position = Engine::Position(
        gridPosition.getX() + ((row +1) * firstCellX) + ((row + 1) * lineWidth),
        gridPosition.getY() + ((line + 1) * firstCellY) + ((line + 1) * lineWidth)
    );
}

void Cell::draw()
{
    SDL_FRect rect;
    rect.x = _position.getX();
    rect.y = _position.getY();
    rect.w = _dimensions.getWidth();
    rect.h = _dimensions.getHeight();

    switch (_state)
    {
        case CellState::INITIAL:
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 64); 
            break;

        case CellState::HIT:
            SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 192); 
            break;

        case CellState::MISSED:
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 192); 
            break;
    }
    
    SDL_RenderFillRect(_renderer, &rect);
}
