#include "player/human/human_player.hpp"
#include "player/human/carrier.hpp"
#include "player/human/battleship.hpp"
#include "player/human/cruiser.hpp"
#include "player/human/submarine.hpp"
#include "player/human/destroyer.hpp"
#include <algorithm>

using namespace Player;
using namespace Player::Human;

HumanPlayer::HumanPlayer()
:   Player::Player()
{
    Engine::Engine & engine = Engine::Engine::getInstance();
    
    Engine::Resolution defaultResolution(1280, 720);
    Engine::Resolution currentResolution = engine.getConfiguration()->getResolution();

    _playerGrid = std::make_unique<HumanGrid>(Engine::Position(25,25).scale(defaultResolution, currentResolution));
    _opponentGrid = std::make_unique<Grid>(Engine::Position(675,25).scale(defaultResolution, currentResolution));

    _startButton = std::make_unique<StartButton>(
        Engine::Position(1100, 625).scale(defaultResolution, currentResolution), 
        currentResolution
    );

    _shipCounter = std::make_unique<ShipCounter>(
        Engine::Position(74, 610).scale(defaultResolution, currentResolution),
        currentResolution
    );

    _gameSummary = std::make_unique<GameSummary>(currentResolution);

    _ships = std::array<std::shared_ptr<Ship>, 5> ({
        std::make_shared<Carrier>(Engine::Position(675, 75).scale(defaultResolution, currentResolution)),
        std::make_shared<Battleship>(Engine::Position(675,150).scale(defaultResolution, currentResolution)),
        std::make_shared<Cruiser>(Engine::Position(675,225).scale(defaultResolution, currentResolution)),
        std::make_shared<Submarine>(Engine::Position(675,300).scale(defaultResolution, currentResolution)),
        std::make_shared<Destroyer>(Engine::Position(675,375).scale(defaultResolution, currentResolution))
    });

    _eventBus->registerHandler<Events::GameStarted>(std::bind(
        &HumanPlayer::handleGameStarted, this, std::placeholders::_1
    ));

    _eventBus->registerHandler<Events::ShotFired>(std::bind(
        &HumanPlayer::handleShotFired, this, std::placeholders::_1
    ));

    _eventBus->registerHandler<Events::ShotResultAnnounced>(std::bind(
        &HumanPlayer::handleShotResultAnnounced, this, std::placeholders::_1
    ));
}

HumanPlayer::~HumanPlayer()
{
}

void HumanPlayer::processEvent(const SDL_Event & event)
{
    switch (_state)
    {
        case PlayerState::PLACING_SHIPS:
            processShipEvent(event);
            processStartButtonEvent(event);
            break;

        case PlayerState::READY_TO_PLAY:
            break;

        case PlayerState::DEFENDING:
            break;

        case PlayerState::ATTACKING:
            processAttackEvents(event);
            break;
        
        case PlayerState::GAME_OVER:
            _gameSummary->processEvent(event);
            break;

        default:
            break;
    }
}

void HumanPlayer::update()
{
    switch (_state)
    {
        case PlayerState::PLACING_SHIPS:
            updateShips();
            updateStartButton();
            break;

        case PlayerState::READY_TO_PLAY:
            _shipCounter->update();
            break;

        case PlayerState::DEFENDING:
            if (_needToAnnounceShotResult)
            {
                _eventBus->publish(std::make_shared<Events::ShotResultAnnounced>(_lastShotResult));
                _needToAnnounceShotResult = false;
                _state = PlayerState::ATTACKING;
            }
            _shipCounter->update();
            break;

        case PlayerState::ATTACKING:
            _shipCounter->update();
            break;

        case PlayerState::GAME_OVER:
            _shipCounter->update();
            _gameSummary->update();
            break;

        default:
            break;
    }
}

void HumanPlayer::draw()
{
    _playerGrid->draw();

    std::for_each(_ships.cbegin(), _ships.cend(), [](const std::shared_ptr<Ship> & ship)
    {
        ship->draw();
    });
    
    switch (_state)
    {
        case PlayerState::PLACING_SHIPS:
            _startButton->draw();
            break;

        case PlayerState::READY_TO_PLAY:
            break;

        case PlayerState::DEFENDING:
        case PlayerState::ATTACKING:
            _opponentGrid->draw();
            _shipCounter->draw();
            break;

        case PlayerState::GAME_OVER:
            _opponentGrid->draw();
            _gameSummary->draw();
            break;
    }
}

void HumanPlayer::processShipEvent(const SDL_Event & event)
{
    switch (event.type)
    {
        case SDL_EVENT_MOUSE_MOTION:
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:   
            std::for_each(_ships.cbegin(), _ships.cend(), [event](const std::shared_ptr<Ship> & ship)
            {
                ship->processEvent(event);
            });
            break;

        default:
            break;
    }
}

void HumanPlayer::processStartButtonEvent(const SDL_Event & event)
{
    switch (event.type)
    {
        case SDL_EVENT_MOUSE_MOTION:
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:   
            _startButton->processEvent(event);
            break;

        default:
            break;
    }
}

void HumanPlayer::processAttackEvents(const SDL_Event & event)
{
    Cell * clickedCell = nullptr;
    std::string clickedCellPositionName = "";

    switch (event.type)
    {
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            clickedCell = _opponentGrid->getClickedCell(event.button.x, event.button.y);
            
            if (clickedCell && clickedCell->getState() == CellState::INITIAL)
            {
                clickedCellPositionName = clickedCell->getPositionName();

                _state = PlayerState::DEFENDING;
                _eventBus->publish(std::make_shared<Events::ShotFired>(PlayerType::PLAYER, clickedCellPositionName));
            }
            break;

        default:
            break;
    }
}

void HumanPlayer::updateShips()
{
    std::for_each(_ships.cbegin(), _ships.cend(), [this](const std::shared_ptr<Ship> & ship)
    {
        ship->update();

        if (ship->isSnapRequested())
            _playerGrid->snap(*ship);

        if (ship->isCollisionCheckRequested())
        {
            std::for_each(_ships.cbegin(), _ships.cend(), [&ship](const std::shared_ptr<Ship> & otherShip)
            {
                if (otherShip != ship && ship->collidesWith(*otherShip))
                    ship->resetPosition();
            });
        }
    });
}

void HumanPlayer::updateStartButton()
{
    _startButton->update();

    if (! _startButton->isEnabled() && allShipsOnGrid())
        _startButton->enable();
    else if (_startButton->isEnabled() && ! allShipsOnGrid())
        _startButton->disable();    
}


bool HumanPlayer::allShipsOnGrid() const
{
    return std::all_of(_ships.cbegin(), _ships.cend(), [](const std::shared_ptr<Ship> & ship)
    {
        return ship->isOnGrid();
    });
}

void HumanPlayer::handleGameStarted(std::shared_ptr<Events::GameStarted> event)
{
    _state = event->getFirstPlayer() == PlayerType::PLAYER ? PlayerState::ATTACKING : PlayerState::DEFENDING;
}

void HumanPlayer::handleShotFired(std::shared_ptr<Events::ShotFired> event)
{
    if (event->getInitiator() == PlayerType::OPPONENT)
    {
        Events::ShotResult result = Events::ShotResult::MISS;
        bool resultFound = false;

        for (const auto & ship : _ships)
        {
            if (! resultFound)
            {
                result = ship->applyShot(event->getPositionName());

                if (result != Events::ShotResult::MISS)
                    resultFound = true;
            }
        }

        if (result == Events::ShotResult::MISS)
        {
            Cell & cell = _playerGrid->getCell(event->getPositionName());
            cell.setState(CellState::MISSED);
        }
        else if (result == Events::ShotResult::SUNK)
        {
            _remainingShipsCount--;
        }

        _lastShotResult = Events::ShotResultAnnounced(
            PlayerType::PLAYER,
            event->getPositionName(),
            result
        );

        _needToAnnounceShotResult = true;
    }
}

void HumanPlayer::handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event)
{
    // If opponent announces a shot result, player made the shot. And vice versa.
    std::string positionName = event->getPositionName();
    
    if (event->getInitiator() == PlayerType::OPPONENT)
    {
        Cell & cell = _opponentGrid->getCell(positionName);

        if (event->getShotResult() == Events::ShotResult::MISS)
            cell.setState(CellState::MISSED);
        else
            cell.setState(CellState::HIT);
    }
}
