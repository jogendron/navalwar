#include "engine/position.hpp"
#include "engine/engine.hpp"

using namespace Engine;

Position::Position()
: _x (0), _y (0)
{
}

Position::Position(float x, float y)
: _x (x), _y (y)
{
}

Position::~Position()
{
}

const float & Position::getX() const
{
    return _x;
}

const float & Position::getY() const
{
    return _y;
}

void Position::setX(const float & value)
{
    _x = value;
}

void Position::setY(const float & value)
{
    _y = value;
}

Position Position::scale(const Resolution& from, const Resolution& to) const
{
    return Position(
        to.getWidth() * _x / from.getWidth(),
        to.getHeight() * _y / from.getHeight()
    );
}