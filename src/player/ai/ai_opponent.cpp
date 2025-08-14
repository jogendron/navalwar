#include "player/ai/ai_opponent.hpp"

#include "events/opponent_ready.hpp"

#include <set>

using namespace Player::AI;

AIOpponent::AIOpponent() 
:   Player()
{
    _eventBus->registerHandler<Events::GameStarted>(std::bind(
        &AIOpponent::handleGameStarted, this, std::placeholders::_1
    ));

    _eventBus->registerHandler<Events::ShotFired>(std::bind(
        &AIOpponent::handleShotFired, this, std::placeholders::_1
    ));

    _eventBus->registerHandler<Events::ShotResultAnnounced>(std::bind(
        &AIOpponent::handleShotResultAnnounced, this, std::placeholders::_1
    ));
}

AIOpponent::~AIOpponent() 
{
}

void AIOpponent::update()
{
    switch (_state)
    {
        case PlayerState::PLACING_SHIPS:
            placeShips();
            _state = PlayerState::READY_TO_PLAY;
            _eventBus->publish(std::make_shared<Events::OpponentReady>());
            break;

        case PlayerState::READY_TO_PLAY:
            break;

        case PlayerState::DEFENDING:
            if (_needToAnnounceShotResult)
            {
                _eventBus->publish(std::make_shared<Events::ShotResultAnnounced>(_lastShotResult));
                _needToAnnounceShotResult = false;

                if (_remainingShipsCount > 0)
                    _state = PlayerState::ATTACKING;
                else
                    _state = PlayerState::GAME_OVER;
            }
            break;

        case PlayerState::ATTACKING:
            attack();
            break;

        default:
            break;
    }
}

void AIOpponent::placeShips()
{
    placeShip(_carrier, 5);
    placeShip(_battleship, 4);
    placeShip(_cruiser, 3);
    placeShip(_submarine, 3);
    placeShip(_destroyer, 2);
}

void AIOpponent::placeShip(std::vector<std::reference_wrapper<Cell>> & ship, int shipLength)
{
    std::vector<std::vector<std::reference_wrapper<Cell>>> possiblePlacements;
    std::set<std::string> otherShipsCells;

    // Track other ships' cells to avoid overlapping placements
    for (const auto &cell : _carrier) otherShipsCells.insert(cell.get().getPositionName());
    for (const auto &cell : _battleship) otherShipsCells.insert(cell.get().getPositionName());
    for (const auto &cell : _cruiser) otherShipsCells.insert(cell.get().getPositionName());
    for (const auto &cell : _submarine) otherShipsCells.insert(cell.get().getPositionName());
    for (const auto &cell : _destroyer) otherShipsCells.insert(cell.get().getPositionName());

    for (char row = 'A'; row <= 'J'; row++)
    {
        for (int col = 1; col <= 10; col++)
        {
            std::vector<std::reference_wrapper<Cell>> horizontalPlacement;
            std::vector<std::reference_wrapper<Cell>> verticalPlacement;

            bool horizontalPlacementIsValid = true;
            bool verticalPlacementIsValid = true;

            for (int offset = 0; offset < shipLength && (horizontalPlacementIsValid || verticalPlacementIsValid); offset++)
            {
                int offsettedColumn = col + offset;
                int offsettedRow = row + offset;
                std::string horizontalPositionName = "";
                std::string verticalPositionName = "";

                if (offsettedColumn > 10)
                {
                    horizontalPlacementIsValid = false;
                }
                else
                {
                    horizontalPositionName = std::string(1, row) + std::to_string(offsettedColumn);
                    horizontalPlacement.push_back(_playerGrid->getCell(horizontalPositionName));
                }

                if (offsettedRow > 'J')
                {
                    verticalPlacementIsValid = false;
                }
                else
                {
                    verticalPositionName = std::string(1, offsettedRow) + std::to_string(col);
                    verticalPlacement.push_back(_playerGrid->getCell(verticalPositionName));
                }

                // Mark placement invalid if it overlaps with other ships
                for (const auto &otherShipPositionName : otherShipsCells)
                {
                    if (otherShipPositionName == horizontalPositionName)
                    {
                        horizontalPlacementIsValid = false; 
                    }

                    if (otherShipPositionName == verticalPositionName)
                    {
                        verticalPlacementIsValid = false; 
                    }
                }
            }

            if (horizontalPlacementIsValid)
                possiblePlacements.push_back(horizontalPlacement);

            if (verticalPlacementIsValid)
                possiblePlacements.push_back(verticalPlacement);
        }
    }

    // Randomly select a placement from the possiblePlacements vector
    if (!possiblePlacements.empty())
    {
        srand(time(NULL));
        int randomIndex = rand() % possiblePlacements.size();
        const auto & selectedPlacement = possiblePlacements[randomIndex];

        ship.assign_range(selectedPlacement);
    }
}

void AIOpponent::handleGameStarted(std::shared_ptr<Events::GameStarted> event)
{
    if (event->getFirstPlayer() == PlayerType::OPPONENT)
        _state = PlayerState::ATTACKING;
    else
        _state = PlayerState::DEFENDING;
}

void AIOpponent::handleShotFired(std::shared_ptr<Events::ShotFired> event)
{
    if (event->getInitiator() == PlayerType::PLAYER)
    {
        Events::ShotResult result = Events::ShotResult::MISS;
        
        result = applyShotFired(_carrier, event);

        if (result == Events::ShotResult::MISS)
            result = applyShotFired(_battleship, event);

        if (result == Events::ShotResult::MISS)
            result = applyShotFired(_cruiser, event);

        if (result == Events::ShotResult::MISS)
            result = applyShotFired(_submarine, event);

        if (result == Events::ShotResult::MISS)
            result = applyShotFired(_destroyer, event);

        if (result == Events::ShotResult::SUNK)
        {
            _remainingShipsCount--;
        }

        _lastShotResult = Events::ShotResultAnnounced(
            PlayerType::OPPONENT,
            event->getPositionName(),
            result
        );

        _needToAnnounceShotResult = true;
    }
}

Events::ShotResult AIOpponent::applyShotFired(
    std::vector<std::reference_wrapper<Cell>> & ship,
    std::shared_ptr<Events::ShotFired> event
)
{
    Events::ShotResult result = Events::ShotResult::MISS;
    const std::string & positionName = event->getPositionName();
    bool hit = false;
    bool sunk = true;

    for (auto cell : ship)
    {
        if (cell.get().getPositionName() == positionName)
        {
            hit = true;
            cell.get().setState(CellState::HIT);
        }

        sunk = sunk && (cell.get().getState() == CellState::HIT);
    }

    if (sunk && hit) // Don't want to announce a sunk ship if it was not hit
        result = Events::ShotResult::SUNK;
    else if (hit)
        result = Events::ShotResult::HIT;

    return result;
}

void AIOpponent::handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event)
{
    if (event->getInitiator() == PlayerType::PLAYER)
    {
        const std::string & positionName = event->getPositionName();
        Cell & cell = _opponentGrid->getCell(positionName);

        switch (event->getShotResult())
        {
            case Events::ShotResult::HIT:
            case Events::ShotResult::SUNK:
                cell.setState(CellState::HIT);
                break;

            case Events::ShotResult::MISS:
                cell.setState(CellState::MISSED);
                break;
        }
    }
}