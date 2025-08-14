#include "player/human/destroyer.hpp"

using namespace Player::Human;

Destroyer::Destroyer(const Engine::Position & position)
: Ship("destroyer.png", position)
{
}

Destroyer::~Destroyer()
{
}
