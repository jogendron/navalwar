#include "player/human/battleship.hpp"

using namespace Player::Human;

Battleship::Battleship(const Engine::Position & position)
: Ship("battleship.png", position)
{
}

Battleship::~Battleship()
{
}
