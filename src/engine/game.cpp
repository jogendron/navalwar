#include "engine/game.hpp"
#include "engine/engine.hpp"

using namespace Engine;

Game::Game()
{
    Engine& engine = Engine::getInstance();

    _configuration = engine.getConfiguration();
    _resourceManager = engine.getResourceManager();
    _window = engine.getWindow();
    _renderer = engine.getRenderer();
}

void Game::draw(Image * image)
{
    SDL_RenderTexture(_renderer, image->getTexture(), NULL, NULL);
}