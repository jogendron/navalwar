#include "engine/engine.hpp"
#include "ship.hpp"

#include <algorithm>

Ship::Ship(const std::string & imageName, const Engine::Position & position)
:   _state (ShipState::IDLE),
    _orientation (ShipOrientation::HORIZONTAL),
    _shipImage (std::make_unique<Engine::Image>(Engine::Image(imageName, position))),
    _initialPosition (position),
    _position (position),
    _mousePosition (Engine::Position(0,0)),
    _mouseOffset (Engine::Position(0,0)),
    _rotationRequested (false),
    _collisionCheckRequested (false)
{
    Engine::Engine & engine = Engine::Engine::getInstance();
    _screenResolution = engine.getConfiguration()->getResolution();
}

Ship::~Ship()
{
}

const Engine::Position & Ship::getPosition() const
{
    return _position;
}

const Engine::Dimensions & Ship::getDimensions() const
{
    return _shipImage->getDimensions();
}

const ShipOrientation & Ship::getOrientation() const
{
    return _orientation;
}

const bool Ship::isCollisionCheckRequested() const
{
    return _collisionCheckRequested;
}

const bool Ship::collidesWith(const Ship & otherShip)
{
    // Get current ship data
    const Engine::Position & position = getPosition();
    const Engine::Dimensions & dimensions = getDimensions();
    const ShipOrientation & orientation = getOrientation();

    float x = position.getX();
    float y = position.getY();
    int width = dimensions.getWidth();
    int height = dimensions.getHeight();

    if (orientation == ShipOrientation::VERTICAL)
        std::swap(width, height);

    // Get other ship data
    const Engine::Position & otherShipPosition = otherShip.getPosition();
    const Engine::Dimensions & otherShipDimensions = otherShip.getDimensions();
    const ShipOrientation & otherShipOrientation = otherShip.getOrientation();

    float otherX = otherShipPosition.getX();
    float otherY = otherShipPosition.getY();
    int otherWidth = otherShipDimensions.getWidth();
    int otherHeight = otherShipDimensions.getHeight();

    if (otherShipOrientation == ShipOrientation::VERTICAL)
        std::swap(otherWidth, otherHeight);

    // We don't need collision check anymore
    _collisionCheckRequested = false;

    // Check collision
    bool xOverlap = x < (otherX + otherWidth) && (x + width) > otherX;
    bool yOverlap = y < (otherY + otherHeight) && (y + height) > otherY;

    return xOverlap && yOverlap;
}

void Ship::resetPosition()
{
    Engine::Position & imagePosition = _shipImage->getPosition();

    if (_orientation == ShipOrientation::VERTICAL)
        rotate();

    _position = _initialPosition;    
    imagePosition.setX(_position.getX());
    imagePosition.setY(_position.getY());

    _cells.clear();
}

const bool Ship::isSnapRequested() const
{
    return _snapRequested;
}
        
void Ship::snap(const Engine::Position & position, std::vector<std::reference_wrapper<const Cell>> & cells)
{   
    _position = position;
    _snapRequested = false;

    Engine::Position & imagePosition = _shipImage->getPosition();
    int xLostFromRotation = 0;

    if (_orientation == ShipOrientation::VERTICAL)
        xLostFromRotation = _shipImage->getDimensions().getHeight();

    imagePosition.setX(position.getX() + xLostFromRotation);
    imagePosition.setY(position.getY());

    _cells = cells;
    _collisionCheckRequested = true;
}

void Ship::failSnap()
{
    _cells.clear();

    _snapRequested = false;
    _collisionCheckRequested = true;
}

bool Ship::isOnGrid() const
{
    return ! _cells.empty();
}

void Ship::processEvent(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_EVENT_MOUSE_MOTION:
            if (_state == ShipState::DRAGGING)
            {
                _mousePosition.setX(event.motion.x);
                _mousePosition.setY(event.motion.y);
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (_state == ShipState::IDLE)
            {
                if (shipWasClicked(event))
                {
                    Engine::Position & position = _shipImage->getPosition();

                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        _mousePosition.setX(event.button.x);
                        _mousePosition.setY(event.button.y);
                        _mouseOffset.setX(event.button.x - position.getX());
                        _mouseOffset.setY(event.button.y - position.getY());
                        _state = ShipState::DRAGGING;
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        _rotationRequested = true;
                    }

                    _cells.clear();
                }
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (_state == ShipState::DRAGGING)
                _state = ShipState::DROPPING;
            break;

        default:
            break;
    }
}

void Ship::update()
{
    const Engine::Dimensions & imageDimensions = getDimensions();
    int imageWidth = imageDimensions.getWidth();
    int imageHeight = imageDimensions.getHeight();

    if (_orientation == ShipOrientation::VERTICAL)
        std::swap(imageWidth, imageHeight);

    Engine::Position & imagePosition = _shipImage->getPosition();

    switch (_state)
    {
        case ShipState::IDLE:
            if (_rotationRequested)
            {
                rotate();
                _rotationRequested = false;
            }
            break;

        case ShipState::DRAGGING:
            _position.setX(_mousePosition.getX() - _mouseOffset.getX());
            _position.setY(_mousePosition.getY() - _mouseOffset.getY());

            imagePosition.setX(_position.getX());
            imagePosition.setY(_position.getY());
            break;

        case ShipState::DROPPING:
            _state = ShipState::IDLE;

            if (_orientation == ShipOrientation::VERTICAL)
                _position.setX(_position.getX() - _shipImage->getDimensions().getHeight());

            if ( // Put ship back to original position if out of screen
                _position.getX() <= ((imageWidth / 2) * -1)
                || _position.getX() >= (_screenResolution.getWidth() - (imageWidth / 2))
                || _position.getY() <= ((imageHeight / 2) * -1)
                || _position.getY() >= (_screenResolution.getHeight() - (imageHeight / 2))
            )
            {
                resetPosition();
            }
            else // Ship was moved within screen. Request snap from grid
            {
                _snapRequested = true;
            }
            break;

        default:
            break;
    }
}

void Ship::draw()
{
    _shipImage->draw();
}

bool Ship::shipWasClicked(const SDL_Event & event)
{
    Engine::Dimensions dimensions = _shipImage->getDimensions();
    int width = dimensions.getWidth();
    int height = dimensions.getHeight();
    
    // Width and height are inverted when we rotate 90 degrees
    if (_orientation == ShipOrientation::VERTICAL) 
        std::swap(width, height);

    return 
        event.button.x >= (_position.getX())
        && event.button.x <= (_position.getX() + width)
        && event.button.y >= _position.getY()
        && event.button.y <= (_position.getY() + height);
}

void Ship::rotate()
{
    Engine::Position & imagePosition = _shipImage->getPosition();

    SDL_FPoint rotationCenter;
    rotationCenter.x = 0;
    rotationCenter.y = 0;

    _shipImage->setRotationCenter(rotationCenter);

    if (_orientation == ShipOrientation::HORIZONTAL)
    {
        _shipImage->setRotation(90);
        
        int xLostFromRotation = _shipImage->getDimensions().getHeight();
        imagePosition.setX(imagePosition.getX() + xLostFromRotation);

        _orientation = ShipOrientation::VERTICAL;
    }
    else
    {
        _shipImage->setRotation(0);

        int xGainedFromRotation = _shipImage->getDimensions().getHeight();
        imagePosition.setX(imagePosition.getX() - xGainedFromRotation);

        _orientation = ShipOrientation::HORIZONTAL;
    }

    _cells.clear();
    _snapRequested = true;
    _collisionCheckRequested = true;
}