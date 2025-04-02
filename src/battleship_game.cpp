#include "battleship_game.hpp"

BattleshipGame::BattleshipGame()
: Game(), _state (BattleshipGameState::PRE_GAME)
{
    _background = std::make_unique<Engine::Image>("background.png");
    _playerGrid = std::make_unique<Grid>(Engine::Position(25,25));
    _enemyGrid = std::make_unique<Grid>(Engine::Position(675,25));
}

BattleshipGame::~BattleshipGame()
{
}

void BattleshipGame::update()
{
}

void BattleshipGame::render()
{
    _background->draw();
    _playerGrid->draw();

    if (_state != BattleshipGameState::PRE_GAME)
        _enemyGrid->draw();
}