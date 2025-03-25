#include "engine/image.hpp"
#include "engine/engine.hpp"
#include <iostream>
#include <sstream>

using namespace Engine;

Image::Image(const std::string & fileName)
{
    Engine& engine = Engine::getInstance();
    
    _resourceManager = engine.getResourceManager();
    
    Resolution res = engine.getConfiguration()->getResolution();

    std::ostringstream oss;
    oss << "../share/battleship/images/";
    oss << res.getWidth() << "x" << res.getHeight() << "/";
    oss << fileName;

    _path = oss.str();
}

Image::~Image()
{
}

SDL_Texture * Image::getTexture()
{
    if (! _texture)
        _texture = _resourceManager->getTexture(_path);

    return _texture.get();
}