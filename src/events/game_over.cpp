#include "events/game_over.hpp"

Events::GameOver::GameOver(PlayerType winner)
: Engine::Event(), _winner(winner)
{
}

Events::GameOver::~GameOver()
{
}

PlayerType Events::GameOver::getWinner() const
{
    return _winner;
}