#include "player/opponent/easy_computer_opponent.hpp"
#include <vector>

using namespace Player::Opponent;

EasyComputerOpponent::EasyComputerOpponent()
: ComputerOpponent()
{
}

EasyComputerOpponent::~EasyComputerOpponent()
{
}

void EasyComputerOpponent::attack()
{
    attackRandomCell();
}
