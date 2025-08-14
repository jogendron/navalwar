#include "player/player.hpp"
#include "engine/engine.hpp"

namespace Player
{

    Player::Player()
    :   Engine::Entity(),
        _state(PlayerState::PLACING_SHIPS),
        _remainingShipsCount(5),
        _lastShotResult(Events::ShotResultAnnounced(PlayerType::OPPONENT, "", Events::ShotResult::MISS)),
        _needToAnnounceShotResult(false)
    {
        Engine::Engine & engine = Engine::Engine::getInstance();
        _eventBus = engine.getEventBus();
        _logger = engine.getLogger();

        Engine::Position defaultPosition = Engine::Position(0,0);
        Engine::Resolution defaultResolution(1280, 720);
        Engine::Resolution currentResolution = engine.getConfiguration()->getResolution();

        _playerGrid = std::make_unique<Grid>(Engine::Position(25,25).scale(defaultResolution, currentResolution));
        _opponentGrid = std::make_unique<Grid>(Engine::Position(675,25).scale(defaultResolution, currentResolution));
    }

    Player::Player(std::unique_ptr<Grid> playerGrid)
    :   Engine::Entity(),
        _state(PlayerState::PLACING_SHIPS),
        _lastShotResult(Events::ShotResultAnnounced(PlayerType::OPPONENT, "", Events::ShotResult::MISS)),
        _needToAnnounceShotResult(false)
    {
        Engine::Engine & engine = Engine::Engine::getInstance();
        _eventBus = engine.getEventBus();
        _logger = engine.getLogger();

        Engine::Position defaultPosition = Engine::Position(0,0);
        Engine::Resolution defaultResolution(1280, 720);
        Engine::Resolution currentResolution = engine.getConfiguration()->getResolution();

        _playerGrid = std::move(playerGrid);
        _opponentGrid = std::make_unique<Grid>(Engine::Position(675,25).scale(defaultResolution, currentResolution));

        _eventBus->registerHandler<Events::GameOver>(std::bind(
            &Player::handleGameOver, this, std::placeholders::_1
        ));
    }

    Player::~Player()
    {
    }

    PlayerState Player::getState() const
    {
        return _state;
    }
 
    const int Player::getRemainingShipsCount() const
    {
        return _remainingShipsCount;
    }

    void Player::handleGameOver(std::shared_ptr<Events::GameOver> event)
    {
        _state = PlayerState::GAME_OVER;
    }
}
