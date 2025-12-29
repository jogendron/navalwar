#include "player/human/stat_counter.hpp"
#include "engine/engine.hpp"
#include "engine/resolution.hpp"

#include <sstream>

using namespace Player::Human;

StatCounter::StatCounter(
    const Engine::Position & position,
    const Engine::Resolution & currentResolution
)
:   _playerChanged(false),
    _playerShipsLeft(5),
    _opponentChanged(false),
    _opponentShipsLeft(5)
{
    Engine::Engine & engine = Engine::Engine::getInstance();
    _eventBus = engine.getEventBus();

    _localization = engine.getLocalization();

    Engine::Resolution defaultResolution = Engine::Resolution(1280, 720);
    const Engine::Resolution & resolution = engine.getConfiguration()->getResolution();

    int defaultfontSize = 28;
    int fontSize = (defaultfontSize * currentResolution.getHeight()) / defaultResolution.getHeight();
    _font = std::make_unique<Engine::Font>("DejaVuSans.ttf", fontSize);

    _playerPanelBackground = std::make_unique<Engine::Image>(Engine::Image("player_panel.png", position));
    _playerText = createShipsLeftText(5);

    const Engine::Dimensions & playerPanelDimensions = _playerPanelBackground->getDimensions();
    const Engine::Dimensions & playerTextDimensions = _playerText->getDimensions();
    
    _playerText->setPosition(
        Engine::Position(
            position.getX() + ((playerPanelDimensions.getWidth() - playerTextDimensions.getWidth()) / 2),
            position.getY() + ((playerPanelDimensions.getHeight() - playerTextDimensions.getHeight()) / 2)
        )
    );

    const Engine::Position opponnentPanelOffset = Engine::Position(650, 0).scale(defaultResolution, currentResolution);
    _opponentPanelBackground = std::make_unique<Engine::Image>(Engine::Image(
        "opponent_panel.png", 
        Engine::Position(position.getX() + opponnentPanelOffset.getX(), position.getY())
    ));

    _opponentText = createShipsLeftText(5);
    _opponentText->setPosition(
        Engine::Position(
            _playerText->getPosition().getX() + opponnentPanelOffset.getX(),
            _playerText->getPosition().getY()
        )
    );

    _eventBus->registerHandler<Events::ShotResultAnnounced>(std::bind(
        &StatCounter::handleShotResultAnnounced, this, std::placeholders::_1
    ));
}

StatCounter::~StatCounter()
{
}

void StatCounter::update()
{
    if (_playerChanged)
    {
        const Engine::Position position = _playerText->getPosition();

        _playerText = createShipsLeftText(_playerShipsLeft);
        _playerText->setPosition(position);

        _playerChanged = false;
    }

    if (_opponentChanged)
    {
        const Engine::Position position = _opponentText->getPosition();

        _opponentText = createShipsLeftText(_opponentShipsLeft);
        _opponentText->setPosition(position);

        _opponentChanged = false;
    }
}

void StatCounter::draw()
{
    _playerPanelBackground->draw();
    _playerText->draw();

    _opponentPanelBackground->draw();
    _opponentText->draw();
}

std::shared_ptr<Engine::Image> StatCounter::createShipsLeftText(int shipsLeft) const
{
    std::ostringstream oss;
    oss << _localization->getTranslation("stat-counter.ships-left") << shipsLeft;

    return _font->createImage(
        oss.str(),
        SDL_Color{255, 255, 255, 255}
    );
}

void StatCounter::handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event)
{
    if (event->getShotResult() == Events::ShotResult::SUNK)
    {
        if (event->getInitiator() == PlayerType::PLAYER)
        {
            _playerShipsLeft--;
            _playerChanged = true;
        }
        else
        {
            _opponentShipsLeft--;
            _opponentChanged = true;
        }
    }
}