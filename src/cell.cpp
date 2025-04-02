#include "cell.hpp"
#include "engine/engine.hpp"

Cell::Cell()
: _state (CellState::INITIAL)
{
}

Cell::~Cell()
{
}

void Cell::setState(const CellState& state)
{
    _state = state;
}

void Cell::setPosition(int row, int line, const Engine::Position& gridPosition)
{
    Engine::Engine& engine = Engine::Engine::getInstance();
    Engine::Resolution resolution = engine.getConfiguration()->getResolution();

    float firstCellX = 0;
    float firstCellY = 0;
    float lineWidth = 0;

    switch (resolution.getWidth())
    {
        case 1280:
            firstCellX = 50;
            firstCellY = 50;
            lineWidth = 1.35;

            _rect.w = 48;
            _rect.h = 48;
            break;

        case 1920:
            firstCellX = 72;
            firstCellY = 72;
            lineWidth = 5;

            _rect.w = 72;
            _rect.h = 72;
            break;

        case 3840:
            firstCellX = 144;
            firstCellY = 144;
            lineWidth = 10;

            _rect.w = 144;
            _rect.h = 144;
            break;
    }

    _rect.x = gridPosition.getX() + (row * firstCellX) + (row * lineWidth);
    _rect.y = gridPosition.getY() + (line * firstCellY) + (line * lineWidth);
}

void Cell::draw()
{
    switch (_state)
    {
        case CellState::INITIAL:
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 64); 
            break;

        case CellState::TOUCHED:
            SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 128); 
            break;

        case CellState::MISSED:
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 128); 
            break;
    }
    
    SDL_RenderFillRect(_renderer, &_rect);
}