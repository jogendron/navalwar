#include "player/human/start_button.hpp"
#include "events/player_ready.hpp"

using namespace Player::Human;

StartButton::StartButton(
    const Engine::Position & position,
    const Engine::Resolution & currentResolution
)
: Engine::Entity()
{
    Engine::Engine & engine = Engine::Engine::getInstance();
    _eventBus = engine.getEventBus();
    _localization = engine.getLocalization();

    Engine::Resolution defaultResolution(1280, 720);

    Engine::Dimensions frameDimensions = Engine::Dimensions(150, 66).scale(defaultResolution, currentResolution);

    std::vector<Engine::Position> frames = {
        Engine::Position(0, 0).scale(defaultResolution, currentResolution),
        Engine::Position(150, 0).scale(defaultResolution, currentResolution)
    };

    int defaultfontSize = 28;
    int fontSize = (defaultfontSize * currentResolution.getHeight()) / defaultResolution.getHeight();
    _font = std::make_unique<Engine::Font>("DejaVuSans.ttf", fontSize);

    std::string text = _localization->getTranslation("start-button");
    _startIdleText = _font->createImage(text, SDL_Color{255, 255, 255, 255});
    _startClickingText = _font->createImage(text, SDL_Color{0, 0, 0, 255});

    _sprite = std::make_unique<Engine::Sprite>(
        "start_button_ttf.png",
        position,
        frameDimensions,
        frames
    );

    Engine::Position& spritePosition = _sprite->getPosition();
    Engine::Dimensions textDimensions = _startIdleText->getDimensions();
    _startIdleText->setPosition(
        Engine::Position(
            spritePosition.getX() + ((frameDimensions.getWidth() - textDimensions.getWidth()) / 2),
            spritePosition.getY() + ((frameDimensions.getHeight() - textDimensions.getHeight()) / 2)
        )
    );
    _startClickingText->setPosition(_startIdleText->getPosition());
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
                _clicking = true;
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (isEnabled() && _clicking)
            {
                _clicking = false;
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

        _eventBus->publish(std::make_shared<Events::PlayerReady>());
    }
}

void StartButton::draw()
{
    _sprite->draw();

    if (_clicking)
        _startClickingText->draw();
    else
        _startIdleText->draw();
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