#include "events/game_started.hpp"

Events::GameStarted::GameStarted(PlayerType firstPlayer)
:   Engine::Event(),
    _firstPlayer(firstPlayer)
{
}

Events::GameStarted::~GameStarted()
{
}

PlayerType Events::GameStarted::getFirstPlayer() const
{
    return _firstPlayer;
}