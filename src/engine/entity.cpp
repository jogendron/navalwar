#include "engine/entity.hpp"
#include "engine/engine.hpp"

using namespace Engine;

Entity::Entity()
{
    Engine& engine = Engine::getInstance();

    _resourceManager = engine.getResourceManager();

    _window = engine.getWindow();
    _renderer = engine.getRenderer();
}

Entity::~Entity()
{
}

void Entity::processEvent(const SDL_Event & event)
{
}

void Entity::update()
{
}

void Entity::draw()
{
}