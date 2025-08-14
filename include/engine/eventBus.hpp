#ifndef __BATTLESHIP_ENGINE_EVENTBUS_HPP
#define __BATTLESHIP_ENGINE_EVENTBUS_HPP

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <typeindex>
#include <vector>

#include "engine/event.hpp"

namespace Engine
{
    class EventBus
    {
        public:
            EventBus();
            ~EventBus();

            template <typename T>
            void registerHandler(std::function<void(std::shared_ptr<T>)> handler);
            
            void publish(std::shared_ptr<Event> event);

            void processEvents();

        private:
            std::map<std::type_index, std::vector<std::function<void(std::shared_ptr<Event>)>>> _handlers;
            std::list<std::shared_ptr<Event>> _events;
    };
}

template <typename T>
void Engine::EventBus::registerHandler(std::function<void(std::shared_ptr<T>)> handler)
{
    static_assert(std::is_base_of_v<Event, T>, "T must inherit from Event");

    std::type_index typeIndex(typeid(T));

    if (_handlers.find(typeIndex) == _handlers.end())
        _handlers.emplace(typeIndex, std::vector<std::function<void(std::shared_ptr<Event>)>>());

    auto wrapper = [handler](std::shared_ptr<Event> event) {
        auto typedEvent = std::dynamic_pointer_cast<T>(event);
        handler(typedEvent);
    };

    _handlers[typeIndex].push_back(wrapper);
}

#endif