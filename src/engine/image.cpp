#include "engine/image.hpp"
#include "engine/engine.hpp"
#include <iostream>
#include <sstream>

using namespace Engine;

Image::Image(const std::string & fileName)
{
    Engine& engine = Engine::getInstance();
    
    _resourceManager = engine.getResourceManager();
    _window = engine.getWindow();
    _renderer = engine.getRenderer();
    
    Resolution res = engine.getConfiguration()->getResolution();

    std::ostringstream oss;
    oss << "../share/battleship/images/";
    oss << res.getWidth() << "x" << res.getHeight() << "/";
    oss << fileName;

    _path = oss.str();
}

Image::Image(
    const std::string & filename, 
    const Position & position
) 
: Image (filename)
{
    _position = position;
}

Image::~Image()
{
}

const Position & Image::getPosition()
{
    return _position;
}

SDL_Texture * Image::getTexture()
{
    if (! _texture)
        _texture = _resourceManager->getTexture(_path);

    return _texture.get();
}

void Image::draw()
{
    SDL_Texture * texture = getTexture();
    const Position & position = _position;

    SDL_FRect dst;
    dst.w = texture->w;
    dst.h = texture->h;
    dst.x = position.getX();
    dst.y = position.getY();

    SDL_RenderTexture(
        _renderer, 
        texture, 
        NULL, 
        & dst
    );
}