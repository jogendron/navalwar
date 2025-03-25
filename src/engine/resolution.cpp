#include "engine/resolution.hpp"

using namespace Engine;

Resolution::Resolution()
: _width (DEFAULT_WIDTH), _height (DEFAULT_HEIGHT)
{
}

Resolution::Resolution(int width, int height)
: _width (width), _height (height)
{
}

Resolution::~Resolution()
{
}

const int Resolution::getWidth() const
{
    return _width;
}

const int Resolution::getHeight() const
{
    return _height;
}