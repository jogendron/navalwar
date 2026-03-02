#include "engine/eventBus.hpp"

Engine::EventBus::EventBus()
{
}

Engine::EventBus::~EventBus()
{
    _handlers.clear();
}

void Engine::EventBus::publish(std::shared_ptr<Event> event)
{
    _events.push_back(event);
}

void Engine::EventBus::processEvents()
{
    for (const auto& event : _events)
    {
        if (event != nullptr)
        {
            auto & e = * event;
            std::type_index typeIndex = typeid(e);

            auto it = _handlers.find(typeIndex);
            if (it != _handlers.end())
            {
                for (auto& handler : it->second)
                {
                    handler(event);
                }
            }
        }   
    }

    _events.clear();
}

void Engine::EventBus::reset()
{
    _handlers.clear();
    _events.clear();
}