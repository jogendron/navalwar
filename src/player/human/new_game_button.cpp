#include "player/human/new_game_button.hpp"
#include "events/new_game.hpp"

using namespace Player::Human;

NewGameButton::NewGameButton(const Engine::Resolution & currentResolution)
:   Engine::Entity(),
    _clicking(false),
    _clicked(false)
{
    Engine::Engine & engine = Engine::Engine::getInstance();
    _eventBus = engine.getEventBus();
    _localization = engine.getLocalization();

    Engine::Resolution defaultResolution(1280, 720);

    _background = std::make_unique<Engine::Image>(Engine::Image("new_game_button.png"));
    _background->setPosition(Engine::Position(
        currentResolution.getWidth() / 2 - _background->getDimensions().getWidth() / 2,
        currentResolution.getHeight() * 0.9 - _background->getDimensions().getHeight() / 2
    ));

    int defaultFontSize = 48;
    int fontSize = (defaultFontSize * currentResolution.getHeight()) / defaultResolution.getHeight();
    _font = std::make_unique<Engine::Font>("DejaVuSans.ttf", fontSize);

    _text = _font->createImage(_localization->getTranslation("new-game-button"), SDL_Color{255, 255, 255, 255});
    _text->setPosition(
        Engine::Position(
            _background->getPosition().getX() + ((_background->getDimensions().getWidth() - _text->getDimensions().getWidth()) / 2),
            _background->getPosition().getY() + ((_background->getDimensions().getHeight() - _text->getDimensions().getHeight()) / 2)
        )
    );
}

NewGameButton::~NewGameButton()
{
}

void NewGameButton::processEvent(const SDL_Event & event)
{
    switch (event.type)
    {
        case SDL_EVENT_MOUSE_MOTION:
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (buttonWasClicked(event))
            {
                _clicking = true;

                Engine::Position position = _text->getPosition();
                _text = _font->createImage(_localization->getTranslation("new-game-button"), SDL_Color{0, 0, 0, 255});
                _text->setPosition(position);
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (_clicking)
            {
                _clicking = false;
                _clicked = true;

                Engine::Position position = _text->getPosition();
                _text = _font->createImage(_localization->getTranslation("new-game-button"), SDL_Color{255, 255, 255, 255});
                _text->setPosition(position);
            }
            break;

        default:
            break;
    }
}

void NewGameButton::update()
{
    if (_clicked)
    {
        _eventBus->publish(std::make_shared<Events::NewGame>());
        _clicked = false;
    }
}

void NewGameButton::draw()
{
    _background->draw();
    _text->draw();
}

bool NewGameButton::buttonWasClicked(const SDL_Event & event)
{
    Engine::Dimensions dimensions = _background->getDimensions();
    Engine::Position position = _background->getPosition();

    int width = dimensions.getWidth();
    int height = dimensions.getHeight();

    return 
        event.button.x >= (position.getX())
        && event.button.x <= (position.getX() + width)
        && event.button.y >= position.getY()
        && event.button.y <= (position.getY() + height);
}