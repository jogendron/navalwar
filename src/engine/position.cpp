#include "engine/position.hpp"

using namespace Engine;

Position::Position()
: _x (0), _y (0)
{
}

Position::Position(float x, float y)
: _x (x), _y (y)
{
}

Engine::Position::~Position()
{
}

const float & Engine::Position::getX() const
{
    return _x;
}

const float & Engine::Position::getY() const
{
    return _y;
}

void Engine::Position::setX(const float & value)
{
    _x = value;
}

void Engine::Position::setY(const float & value)
{
    _y = value;
}