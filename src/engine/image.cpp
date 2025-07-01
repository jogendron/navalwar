#include "engine/image.hpp"
#include "engine/engine.hpp"
#include <sstream>

using namespace Engine;

Image::Image(const std::string & fileName)
:   _position (Position(0,0)), 
    _dimensions (Dimensions(0,0)),
    _rotation (0)
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

    _rotationCenter.x = 0;
    _rotationCenter.y = 0;
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

Position & Image::getPosition()
{
    return _position;
}

SDL_Texture * Image::getTexture()
{
    if (! _texture)
        _texture = _resourceManager->getTexture(_path);

    return _texture.get();
}

const Dimensions & Image::getDimensions()
{
    if (_dimensions.getWidth() == 0 || _dimensions.getHeight() == 0)
    {
        if (! _texture)
            _texture = _resourceManager->getTexture(_path);

        _dimensions = Dimensions(_texture->w, _texture->h);
    }
    
    return _dimensions;
}

const float & Image::getRotation() const
{
    return _rotation;
}
            
const SDL_FPoint & Image::getRotationCenter() const
{
    return _rotationCenter;
}

void Image::setPosition(const Position & position)
{
    _position = position;
}

void Image::setRotation(const float & rotation)
{
    _rotation = rotation;
}
            
void Image::setRotationCenter(SDL_FPoint center)
{
    _rotationCenter = center;
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

    if (_rotation == 0 || _rotation == 360)
    {
        SDL_RenderTexture(
            _renderer, 
            texture, 
            NULL, 
            & dst
        );
    }
    else
    {
        SDL_RenderTextureRotated(
            _renderer, 
            texture, 
            NULL, 
            & dst, 
            _rotation, 
            & _rotationCenter, 
            SDL_FLIP_NONE
        );
    }
    
}