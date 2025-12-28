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
    oss << "../share/" << engine.getConfiguration()->getGameName() << "/images/";
    oss << res.getWidth() << "x" << res.getHeight() << "/";
    oss << fileName;

    _path = oss.str();

    _rotationCenter.x = 0;
    _rotationCenter.y = 0;

    _texture = _resourceManager->getTexture(_path);
}

Image::Image(
    const std::string & filename, 
    const Position & position
) 
: Image (filename)
{
    _position = position;
}

Image::Image(std::shared_ptr<SDL_Texture> texture)
: _position (Position(0,0)), 
  _dimensions (Dimensions(0,0)),
  _rotation (0)
{
    Engine& engine = Engine::getInstance();
    
    _resourceManager = engine.getResourceManager();
    _window = engine.getWindow();
    _renderer = engine.getRenderer();

    _rotationCenter.x = 0;
    _rotationCenter.y = 0;

    _texture = texture;
}

Image::~Image()
{
}

Position & Image::getPosition()
{
    return _position;
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
    const Position & position = _position;

    SDL_FRect sourceRectangle = getSourceRectangle();
    SDL_FRect destinationRectangle = getDestinationRectangle();

    if (_rotation == 0 || _rotation == 360)
    {
        SDL_RenderTexture(
            _renderer, 
            _texture.get(), 
            & sourceRectangle, 
            & destinationRectangle
        );
    }
    else
    {
        SDL_RenderTextureRotated(
            _renderer, 
            _texture.get(), 
            & sourceRectangle, 
            & destinationRectangle, 
            _rotation, 
            & _rotationCenter, 
            SDL_FLIP_NONE
        );
    }
}

SDL_FRect Image::getSourceRectangle()
{
    SDL_FRect sourceRectangle;

    sourceRectangle.w = _texture->w;
    sourceRectangle.h = _texture->h;
    sourceRectangle.x = 0;
    sourceRectangle.y = 0;

    return sourceRectangle;
}

SDL_FRect Image::getDestinationRectangle()
{
    SDL_FRect destinationRectangle;

    destinationRectangle.w = _texture->w;
    destinationRectangle.h = _texture->h;
    destinationRectangle.x = _position.getX();
    destinationRectangle.y = _position.getY();

    return destinationRectangle;
}