#include "engine/sprite.hpp"

Engine::Sprite::Sprite(
    const std::string & fileName,
    const Dimensions & frameDimensions,
    const std::vector<Position> & frames
)
    : Image(fileName),
      _frameDimensions(frameDimensions),
      _frames(frames),
      _currentFrameIndex(0)
{
}

Engine::Sprite::Sprite(
    const std::string & filename, 
    const Position & position,
    const Dimensions & frameDimensions,
    const std::vector<Position> & frames
)
    : Image(filename, position),
      _frameDimensions(frameDimensions),
      _frames(frames),
      _currentFrameIndex(0)
{
}

Engine::Sprite::~Sprite()
{
}

const size_t Engine::Sprite::getCurrentFrameIndex() const
{
    return _currentFrameIndex;
}

void Engine::Sprite::setCurrentFrameIndex(size_t index)
{
    if (index >= _frames.size())
        throw std::out_of_range("Frame index out of range");
        
    _currentFrameIndex = index;
}

SDL_FRect Engine::Sprite::getSourceRectangle()
{
    SDL_FRect sourceRectangle;
    
    const Position & framePosition = _frames[_currentFrameIndex];
    sourceRectangle.x = framePosition.getX();
    sourceRectangle.y = framePosition.getY();
    
    sourceRectangle.w = _frameDimensions.getWidth();
    sourceRectangle.h = _frameDimensions.getHeight();
    
    return sourceRectangle;
}

SDL_FRect Engine::Sprite::getDestinationRectangle()
{
    SDL_FRect destinationRectangle;

    destinationRectangle.x = _position.getX();
    destinationRectangle.y = _position.getY();
    destinationRectangle.w = _frameDimensions.getWidth();
    destinationRectangle.h = _frameDimensions.getHeight();

    return destinationRectangle;
}