#include "player/human/cruiser.hpp"

using namespace Player::Human;

Cruiser::Cruiser(const Engine::Position & position)
: Ship("cruiser.png", position)
{
}

Cruiser::~Cruiser()
{
}
