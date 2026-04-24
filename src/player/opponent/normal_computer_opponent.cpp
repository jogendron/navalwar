#include "player/opponent/normal_computer_opponent.hpp"

using namespace Player::Opponent;

NormalComputerOpponent::NormalComputerOpponent()
:   ComputerOpponent(),
    _state(NormalComputerOpponentState::SEARCHING_SHIP),
    _orientationDiscoveryState(OrientationDiscoveryState::CHECKING_LEFT),
    _targetedShipOrientation(TargetedShipOrientation::UNKNOWN),
    _firstHitPosition("")
{
}

NormalComputerOpponent::~NormalComputerOpponent()
{
}

void NormalComputerOpponent::attack()
{
    switch (_state)
    {
        case NormalComputerOpponentState::SEARCHING_SHIP:
            attackRandomCell();
            break;

        case NormalComputerOpponentState::DISCOVERING_SHIP_ORIENTATION:
            discoverShipOrientation();
            break;

        case NormalComputerOpponentState::DESTROYING_SHIP:
            sinkShip();
            break;
    }
}

void NormalComputerOpponent::handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event)
{
    ComputerOpponent::handleShotResultAnnounced(event);

    if (event->getInitiator() == PlayerType::PLAYER)
    {
        switch (event->getShotResult())
        {
            case Events::ShotResult::HIT:
                switch (_state)
                {
                    case NormalComputerOpponentState::SEARCHING_SHIP:
                        _firstHitPosition = event->getPositionName();
                        _state = NormalComputerOpponentState::DISCOVERING_SHIP_ORIENTATION;
                        _orientationDiscoveryState = OrientationDiscoveryState::CHECKING_LEFT;
                        _logger->logDebug("Opponent found a ship at " + _firstHitPosition + " and is now looking for ship orientation.");
                        break;

                    case NormalComputerOpponentState::DISCOVERING_SHIP_ORIENTATION:
                        switch (_orientationDiscoveryState)
                        {
                            case OrientationDiscoveryState::CHECKING_LEFT:
                            case OrientationDiscoveryState::CHECKING_RIGHT:
                                _targetedShipOrientation = TargetedShipOrientation::HORIZONTAL;
                                _logger->logDebug("Opponent discovered that the targeted ship is horizontal.");
                                break;

                            case OrientationDiscoveryState::CHECKING_TOP:
                            case OrientationDiscoveryState::CHECKING_DOWN:
                                _targetedShipOrientation = TargetedShipOrientation::VERTICAL;
                                _logger->logDebug("Opponent discovered that the targeted ship is vertical.");
                                break;
                        }

                        _state = NormalComputerOpponentState::DESTROYING_SHIP;
                        break;

                    default:
                        break;
                }
                break;

            case Events::ShotResult::MISS:
                switch (_state)
                {
                case NormalComputerOpponentState::DISCOVERING_SHIP_ORIENTATION:
                    switch (_orientationDiscoveryState)
                    {
                    case OrientationDiscoveryState::CHECKING_LEFT:
                        _orientationDiscoveryState = OrientationDiscoveryState::CHECKING_TOP;
                        break;

                    case OrientationDiscoveryState::CHECKING_TOP:
                        _orientationDiscoveryState = OrientationDiscoveryState::CHECKING_RIGHT;
                        break;

                    case OrientationDiscoveryState::CHECKING_RIGHT:
                        _orientationDiscoveryState = OrientationDiscoveryState::CHECKING_DOWN;
                        break;

                    case OrientationDiscoveryState::CHECKING_DOWN:
                        _state = NormalComputerOpponentState::SEARCHING_SHIP;
                        break;
                    }
                    break;

                default:
                    break;
                }
                break;

            case Events::ShotResult::SUNK:
                _state = NormalComputerOpponentState::SEARCHING_SHIP;
                _orientationDiscoveryState = OrientationDiscoveryState::CHECKING_LEFT;
                _targetedShipOrientation = TargetedShipOrientation::UNKNOWN;
                _firstHitPosition = "";
                _logger->logDebug("Opponent sunk a ship and is now looking for another one.");
                break;

            default:
                break;
        }
    }
}

void NormalComputerOpponent::discoverShipOrientation()
{
    int lineIndex = _firstHitPosition[0] - 'A';
    int columnIndex = std::stoi(_firstHitPosition.substr(1)) - 1;

    int lineOffset = 0;
    int columnOffset = 0;

    OrientationDiscoveryState nextState = OrientationDiscoveryState::CHECKING_LEFT;
    bool advanceToNextDiscoveryState = false;
    bool confused = false;

    switch (_orientationDiscoveryState)
    {
        case OrientationDiscoveryState::CHECKING_LEFT:
            columnOffset = -1;
            nextState = OrientationDiscoveryState::CHECKING_TOP;
            break;

        case OrientationDiscoveryState::CHECKING_TOP:
            lineOffset = -1;
            nextState = OrientationDiscoveryState::CHECKING_RIGHT;
            break;

        case OrientationDiscoveryState::CHECKING_RIGHT:
            columnOffset = 1;
            nextState = OrientationDiscoveryState::CHECKING_DOWN;
            break;

        case OrientationDiscoveryState::CHECKING_DOWN:
            lineOffset = 1;
            nextState = OrientationDiscoveryState::CHECKING_LEFT;
            confused = true;
            break;
    }

    lineIndex += lineOffset;
    columnIndex += columnOffset;

    if (lineIndex < 0 || lineIndex > 9 || columnIndex < 0 || columnIndex > 9)
    {
        advanceToNextDiscoveryState = true;
    }
    else
    {
        std::string targetPosition = std::string(1, char('A' + lineIndex)) + std::to_string(columnIndex + 1);
        Cell & target = _opponentGrid->getCell(targetPosition);

        if (target.getState() == CellState::INITIAL)
            attackCell(targetPosition); //HandleShotResultAnnounced will take care of advancing to next discovery state if the result is a miss
        else
            advanceToNextDiscoveryState = true;
    }

    // If we enter here, either we were going to attack out of bounds, or the direction we verified was already attacked.
    if (advanceToNextDiscoveryState)
    {
        _orientationDiscoveryState = nextState;

        // If we have verified all 4 directions and found no new cell to attack, then we are confused
        if (confused)
        {
            _logger->logWarning("Opponent got confused while finding ship orientation and is looking for another one");
            _state = NormalComputerOpponentState::SEARCHING_SHIP;
        }
    }
}

void NormalComputerOpponent::sinkShip()
{
    std::string target = "";
    bool foundTarget = false;
    bool needToReverse = false;
    bool triedReverse = false;
    bool confused = false;
    
    int lineOffset = _targetedShipOrientation == TargetedShipOrientation::VERTICAL ? 1 : 0;
    int columnOffset = _targetedShipOrientation == TargetedShipOrientation::HORIZONTAL ? 1 : 0;
    
    int firstLineIndex = _firstHitPosition[0] - 'A';
    int firstColumnIndex = std::stoi(_firstHitPosition.substr(1)) -1;
    int lineIndex = firstLineIndex;
    int columnIndex = firstColumnIndex;

    /*
        Scan right or bottom depending on ship orientation.
        If no target found, try left or top (reverse)
        If still no target found, then we are confused and will look for another ship
    */
    while (! foundTarget && ! confused)
    {
        lineIndex += lineOffset;
        columnIndex += columnOffset;

        if (needToReverse || lineIndex < 0 || lineIndex > 9 || columnIndex < 0 || columnIndex > 9)
        {
            if (!triedReverse) {
                lineIndex = firstLineIndex;
                columnIndex = firstColumnIndex;
                lineOffset *= -1;
                columnOffset *= -1;
                
                triedReverse = true;
                needToReverse = false;
            } else {
                confused = true;
            }

            continue;
        }

        std::string potentialTarget = std::string(1, char('A' + lineIndex)) + std::to_string(columnIndex + 1);
        Cell &cell = _opponentGrid->getCell(potentialTarget);

        if (cell.getState() == CellState::INITIAL)
        {            
            target = potentialTarget;
            foundTarget = true;
        }
        else if (cell.getState() == CellState::MISSED)
        {
            needToReverse = true;
        }       
    }

    if (foundTarget)
    {
        attackCell(target);
    }
    else
    {
        _state = NormalComputerOpponentState::SEARCHING_SHIP;
        _logger->logWarning("Opponent got confused while sinking ship and is looking for another one");
    }
}