#include "player/human/carrier.hpp"

using namespace Player::Human;

Carrier::Carrier(const Engine::Position & position)
: Ship("carrier.png", position)
{
}

Carrier::~Carrier()
{
}
