#include "battleship_game.hpp"

BattleshipGame::BattleshipGame()
: Game()
{
    _background = std::make_unique<Engine::Image>("background.png");
}

BattleshipGame::~BattleshipGame()
{
}

void BattleshipGame::update()
{
}

void BattleshipGame::render()
{
    draw(_background.get());
}