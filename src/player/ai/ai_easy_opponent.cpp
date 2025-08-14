#include "player/ai/ai_easy_opponent.hpp"
#include <vector>

using namespace Player::AI;

AIEasyOpponent::AIEasyOpponent()
: AIOpponent()
{
}

AIEasyOpponent::~AIEasyOpponent()
{
}

void AIEasyOpponent::attack()
{
    std::vector<std::string> untouchedCells;

    for (char row = 'A'; row <= 'J'; row++)
    {
        for (int col = 1; col <= 10; col++)
        {
            std::string positionName = std::string(1, row) + std::to_string(col);
            Cell & cell = _opponentGrid->getCell(positionName);

            if (cell.getState() == CellState::INITIAL)
                untouchedCells.push_back(positionName);
        }
    }

    srand(time(NULL));
    int index = rand() % untouchedCells.size();
    std::string target = untouchedCells[index];

    _state = PlayerState::DEFENDING;
    _eventBus->publish(std::make_shared<Events::ShotFired>(PlayerType::OPPONENT, target));
}
