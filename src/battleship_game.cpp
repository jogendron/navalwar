#include "battleship_game.hpp"
#include "engine/engine.hpp"
#include "engine/resolution.hpp"

#include "player/human/human_player.hpp"
#include "player/ai/ai_easy_opponent.hpp"

#include <algorithm>

BattleshipGame::BattleshipGame()
:   Game(), 
    _state (BattleshipGameState::PRE_GAME),
    _playerIsReady(false),
    _opponentIsReady(false)
{
    Engine::Engine & engine = Engine::Engine::getInstance();

    _eventBus = engine.getEventBus();
    _logger = engine.getLogger();
    
    _background = std::make_unique<Engine::Image>("background.png");
    _player = std::make_unique<Player::Human::HumanPlayer>();
    _opponent = std::make_unique<Player::AI::AIEasyOpponent>();

    _eventBus->registerHandler<Events::PlayerReady>(std::bind(
        &BattleshipGame::handlePlayerReady, this, std::placeholders::_1
    ));

    _eventBus->registerHandler<Events::OpponentReady>(std::bind(
        &BattleshipGame::handleOpponentReady, this, std::placeholders::_1
    ));

    _eventBus->registerHandler<Events::GameStarted>(std::bind(
        &BattleshipGame::handleGameStarted, this, std::placeholders::_1
    ));

    _eventBus->registerHandler<Events::ShotFired>(std::bind(
        &BattleshipGame::handleShotFired, this, std::placeholders::_1
    ));

    _eventBus->registerHandler<Events::ShotResultAnnounced>(std::bind(
        &BattleshipGame::handleShotResultAnnounced, this, std::placeholders::_1
    ));

    _eventBus->registerHandler<Events::GameOver>(std::bind(
        &BattleshipGame::handleGameOver, this, std::placeholders::_1
    ));
}

BattleshipGame::~BattleshipGame()
{
}

void BattleshipGame::processEvent(const SDL_Event & event)
{
    _player->processEvent(event);
}

void BattleshipGame::update()
{
    _eventBus->processEvents();
    _player->update();
    _opponent->update();

    switch (_state)
    {
        case BattleshipGameState::PRE_GAME:           
            if (_playerIsReady && _opponentIsReady)
            {
                _state = BattleshipGameState::GAMING;

                srand(time(NULL));
                bool playerPlaysFirst = rand() % 2 == 0;
                PlayerType firstPlayer = playerPlaysFirst ? PlayerType::PLAYER : PlayerType::OPPONENT;

                _eventBus->publish(std::make_shared<Events::GameStarted>(firstPlayer));
            }
            break;
        
        case BattleshipGameState::GAMING:
            break;

        case BattleshipGameState::POST_GAME:
            break;
    }
}

void BattleshipGame::render()
{
    _background->draw();
    _player->draw();
}

void BattleshipGame::handlePlayerReady(std::shared_ptr<Events::PlayerReady> event)
{
    _logger->logInformation("Player is ready to play");

    _playerIsReady = true;
}

void BattleshipGame::handleOpponentReady(std::shared_ptr<Events::OpponentReady> event)
{
    _logger->logInformation("Opponent is ready to play");

    _opponentIsReady = true;
}

void BattleshipGame::handleGameStarted(std::shared_ptr<Events::GameStarted> event)
{
    bool playerIsAttacking = event->getFirstPlayer() == PlayerType::PLAYER;

    std::string firstPlayer = playerIsAttacking ? "Player" : "Opponent";
    _logger->logInformation("Game started, " + firstPlayer + " plays first");

    _state = BattleshipGameState::GAMING;
}

void BattleshipGame::handleShotFired(std::shared_ptr<Events::ShotFired> event)
{
    std::string initiator = event->getInitiator() == PlayerType::PLAYER ? "Player" : "Opponent";
    _logger->logInformation(initiator + " fired a shot at " + event->getPositionName());
}

void BattleshipGame::handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event)
{
    std::string shotInitiator = event->getInitiator() == PlayerType::PLAYER ? "Opponent" : "Player";
    std::string positionName = event->getPositionName();
    bool gameOver = false;
    PlayerType winner = PlayerType::PLAYER;

    switch (event->getShotResult())
    {
        case Events::ShotResult::HIT:
            _logger->logInformation(shotInitiator + " hit a ship at " + positionName);
            break;
        case Events::ShotResult::SUNK:
            _logger->logInformation(shotInitiator + " sunk a ship with a hit at " + positionName);
            
            switch (event->getInitiator())
            {
                case PlayerType::PLAYER:
                    gameOver = _player->getRemainingShipsCount() <= 0;
                    winner = PlayerType::OPPONENT;
                    break;

                case PlayerType::OPPONENT:
                    gameOver = _opponent->getRemainingShipsCount() <= 0;
                    winner = PlayerType::PLAYER;
                    break;
            }

            if (gameOver)
                _eventBus->publish(std::make_shared<Events::GameOver>(winner));
            break;

        case Events::ShotResult::MISS:
            _logger->logInformation(shotInitiator + " missed at " + positionName);
            break;
    }
}

void BattleshipGame::handleGameOver(std::shared_ptr<Events::GameOver> event)
{
    std::string winner = event->getWinner() == PlayerType::PLAYER ? "Player" : "Opponent";
    _logger->logInformation("Game over. " + winner + " wins!");

    _state = BattleshipGameState::POST_GAME;
}