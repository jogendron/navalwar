#include <algorithm>
#include "battleship_game.hpp"
#include "engine/engine.hpp"
#include "engine/resolution.hpp"

BattleshipGame::BattleshipGame()
: Game(), _state (BattleshipGameState::PRE_GAME)
{
    Engine::Engine & engine = Engine::Engine::getInstance();
    
    Engine::Resolution currentResolution = engine.getConfiguration()->getResolution();
    Engine::Resolution defaultResolution(1280, 720);

    _background = std::make_unique<Engine::Image>("background.png");
    _playerGrid = std::make_unique<Grid>(Engine::Position(25,25).scale(defaultResolution, currentResolution));
    _enemyGrid = std::make_unique<Grid>(Engine::Position(675,25).scale(defaultResolution, currentResolution));

    _ships = std::array<std::unique_ptr<Ship>, 5> ({
        std::make_unique<Carrier>(Engine::Position(675, 75).scale(defaultResolution, currentResolution)),
        std::make_unique<Battleship>(Engine::Position(675,150).scale(defaultResolution, currentResolution)),
        std::make_unique<Cruiser>(Engine::Position(675,225).scale(defaultResolution, currentResolution)),
        std::make_unique<Submarine>(Engine::Position(675,300).scale(defaultResolution, currentResolution)),
        std::make_unique<Destroyer>(Engine::Position(675,375).scale(defaultResolution, currentResolution))
    });
}

BattleshipGame::~BattleshipGame()
{
}

void BattleshipGame::processEvent(const SDL_Event & event)
{
    switch (_state)
    {
        case BattleshipGameState::PRE_GAME:
            processShipEvent(event);
            break;
        
        case BattleshipGameState::GAMING:
            break;

        case BattleshipGameState::POST_GAME:
            break;
    }
}

void BattleshipGame::update()
{
    switch (_state)
    {
        case BattleshipGameState::PRE_GAME:
            updateShips();

            if (allShipsOnGrid())
                _state = BattleshipGameState::GAMING;
                
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
    _playerGrid->draw();

    if (_state != BattleshipGameState::PRE_GAME)
        _enemyGrid->draw();

    std::for_each(_ships.cbegin(), _ships.cend(), [](const std::unique_ptr<Ship> & ship)
    {
        ship->draw();
    });
}

void BattleshipGame::processShipEvent(const SDL_Event & event)
{
    switch (event.type)
    {
        case SDL_EVENT_MOUSE_MOTION:
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:   
            std::for_each(_ships.cbegin(), _ships.cend(), [event](const std::unique_ptr<Ship> & ship)
            {
                ship->processEvent(event);
            });
            break;

        default:
            break;
    }
}

void BattleshipGame::updateShips()
{
    std::for_each(_ships.cbegin(), _ships.cend(), [this](const std::unique_ptr<Ship> & ship)
    {
        ship->update();

        if (ship->isSnapRequested())
            _playerGrid->snap(*ship);

        if (ship->isCollisionCheckRequested())
        {
            std::for_each(_ships.cbegin(), _ships.cend(), [&ship](const std::unique_ptr<Ship> & otherShip)
            {
                if (otherShip != ship && ship->collidesWith(*otherShip))
                    ship->resetPosition();
            });
        }
    });
}

bool BattleshipGame::allShipsOnGrid() const
{
    return std::all_of(_ships.cbegin(), _ships.cend(), [](const std::unique_ptr<Ship> & ship)
    {
        return ship->isOnGrid();
    });
}