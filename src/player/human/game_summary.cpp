#include "player/human/game_summary.hpp"
#include <format>
#include <sstream>
#include <string>

using namespace Player::Human;

GameSummary::GameSummary(
    const Engine::Resolution & currentResolution
)
:   Engine::Entity(),
    _currentResolution(currentResolution),
    _hitsCounter(0),
    _missesCounter(0),
    _precision(0.0f)
{
    Engine::Engine & engine = Engine::Engine::getInstance();
    _eventBus = engine.getEventBus();
    _localization = engine.getLocalization();

    Engine::Resolution defaultResolution(1280, 720);

    int defaultTitleFontSize = 170;
    int titleFontSize = (defaultTitleFontSize * currentResolution.getHeight()) / defaultResolution.getHeight();
    _titleFont = std::make_unique<Engine::Font>("DejaVuSans.ttf", titleFontSize);

    int defaultStatsFontSize = 48;
    int statsFontSize = (defaultStatsFontSize * currentResolution.getHeight()) / defaultResolution.getHeight();
    _statsFont = std::make_unique<Engine::Font>("DejaVuSans.ttf", statsFontSize);
    
    _backgroundArea.x = 0;
    _backgroundArea.y = 0;
    _backgroundArea.w = currentResolution.getWidth();
    _backgroundArea.h = currentResolution.getHeight();

    _eventBus->registerHandler<Events::ShotResultAnnounced>(std::bind(
        &GameSummary::handleShotResultAnnounced, this, std::placeholders::_1
    ));

    _eventBus->registerHandler<Events::GameOver>(std::bind(
        &GameSummary::handleGameOver, this, std::placeholders::_1
    ));
}

GameSummary::~GameSummary()
{
}

void GameSummary::processEvent(const SDL_Event & event)
{
    _newGameButton->processEvent(event);
}

void GameSummary::update()
{
    _newGameButton->update();
}

void GameSummary::draw()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 225); 
    SDL_RenderFillRect(_renderer, &_backgroundArea);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255); 

    if (_titleText)
        _titleText->draw();

    if (_hitsText)
        _hitsText->draw();

    if (_missesText)
        _missesText->draw();

    if (_precisionText)
        _precisionText->draw();

    if (_newGameButton)
        _newGameButton->draw();
}

void GameSummary::handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event)
{
    if (event->getInitiator() == PlayerType::OPPONENT)
    {
        Events::ShotResult result = event->getShotResult();

        if (result == Events::ShotResult::HIT || result == Events::ShotResult::SUNK)
            _hitsCounter++;
        else
            _missesCounter++;

        _precision = 100.0f * _hitsCounter / (_hitsCounter + _missesCounter);
    }
}

void GameSummary::handleGameOver(std::shared_ptr<Events::GameOver> event)
{
    setTitleText(event);
    setHitsText(event);
    setMissesText(event);
    setPrecisionText(event);

    _newGameButton = std::make_unique<NewGameButton>(_currentResolution);
}

void GameSummary::setTitleText(std::shared_ptr<Events::GameOver> event)
{
    std::string key = "game-summary.victory";

    if (event->getWinner() == PlayerType::OPPONENT)
        key = "game-summary.defeat";

    _titleText = _titleFont->createImage(_localization->getTranslation(key), SDL_Color{255, 255, 255, 255});
    _titleText->setPosition(
        Engine::Position(
            _currentResolution.getWidth() / 2 - _titleText->getDimensions().getWidth() / 2,
            50
        )
    );
}

void GameSummary::setHitsText(std::shared_ptr<Events::GameOver> event)
{
    std::ostringstream oss;
    oss << _localization->getTranslation("game-summary.hits") << _hitsCounter;

    _hitsText = _statsFont->createImage(oss.str(), SDL_Color{255, 255, 255, 255});
    _hitsText->setPosition(
        Engine::Position(
            _currentResolution.getWidth() / 2 - _hitsText->getDimensions().getWidth() / 2,
            _titleText->getPosition().getY() + _titleText->getDimensions().getHeight() + 50
        )
    );
}

void GameSummary::setMissesText(std::shared_ptr<Events::GameOver> event)
{
    std::ostringstream oss;
    oss << _localization->getTranslation("game-summary.misses") << _missesCounter;

    _missesText = _statsFont->createImage(oss.str(), SDL_Color{255, 255, 255, 255});
    _missesText->setPosition(
        Engine::Position(
            _currentResolution.getWidth() / 2 - _missesText->getDimensions().getWidth() / 2,
            _hitsText->getPosition().getY() + _hitsText->getDimensions().getHeight() + 20
        )
    );
}

void GameSummary::setPrecisionText(std::shared_ptr<Events::GameOver> event)
{
    std::ostringstream oss;
    oss << _localization->getTranslation("game-summary.precision") << std::format("{:.2f}", _precision) << "%";
    
    _precisionText = _statsFont->createImage(oss.str(), SDL_Color{255, 255, 255, 255});
    _precisionText->setPosition(
        Engine::Position(
            _currentResolution.getWidth() / 2 - _precisionText->getDimensions().getWidth() / 2,
            _missesText->getPosition().getY() + _missesText->getDimensions().getHeight() + 20
        )
    );
}