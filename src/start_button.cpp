#include "start_button.hpp"
#include "engine/engine.hpp"

StartButton::StartButton(
    const Engine::Position & position,
    const Engine::Resolution & currentResolution
)
{
    Engine::Resolution defaultResolution(1280, 720);

    std::vector<Engine::Position> frames = {
        Engine::Position(0, 0).scale(defaultResolution, currentResolution),
        Engine::Position(150, 0).scale(defaultResolution, currentResolution),
        Engine::Position(300, 0).scale(defaultResolution, currentResolution)
    };

    _sprite = std::make_unique<Engine::Sprite>(
        "start_button.png",
        position,
        Engine::Dimensions(150, 66).scale(defaultResolution, currentResolution),
        frames
    );
}

StartButton::~StartButton()
{
}

bool StartButton::isEnabled() const
{
    return _enabled;
}

void StartButton::enable()
{
    _enabled = true;
    _sprite->setCurrentFrameIndex(StartButtonFrames::ENABLED);
}

void StartButton::disable()
{
    _enabled = false;
    _sprite->setCurrentFrameIndex(StartButtonFrames::DISABLED);
}

void StartButton::processEvent(const SDL_Event & event)
{
    switch (event.type)
    {
        case SDL_EVENT_MOUSE_MOTION:
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (isEnabled() && buttonWasClicked(event))
            {
                _sprite->setCurrentFrameIndex(StartButtonFrames::CLICKING);
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (isEnabled() && _sprite->getCurrentFrameIndex() == StartButtonFrames::CLICKING)
            {
                _sprite->setCurrentFrameIndex(StartButtonFrames::ENABLED);
                _clicked = true;
            }
            break;

        default:
            break;
    }
}

void StartButton::update()
{
    if (_clicked)
    {
        _clicked = false;
        
        if (onClick)
            onClick();
    }
}

void StartButton::draw()
{
    _sprite->draw();
}

bool StartButton::buttonWasClicked(const SDL_Event & event)
{
    Engine::Dimensions dimensions = _sprite->getDimensions();
    Engine::Position position = _sprite->getPosition();

    int width = dimensions.getWidth();
    int height = dimensions.getHeight();

    return 
        event.button.x >= (position.getX())
        && event.button.x <= (position.getX() + width)
        && event.button.y >= position.getY()
        && event.button.y <= (position.getY() + height);
}