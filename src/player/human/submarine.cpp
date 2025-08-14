#include "player/human/submarine.hpp"

using namespace Player::Human;

Submarine::Submarine(const Engine::Position & position)
: Ship("submarine.png", position)
{
}

Submarine::~Submarine()
{
}
