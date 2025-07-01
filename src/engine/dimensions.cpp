#include "engine/dimensions.hpp"

using namespace Engine;

Dimensions::Dimensions()
{
}

Dimensions::Dimensions(int width, int height)
: _width (width), _height (height)
{
}

Dimensions::~Dimensions()
{
}

const int Dimensions::getWidth() const
{
    return _width;
}

const int Dimensions::getHeight() const
{
    return _height;
}