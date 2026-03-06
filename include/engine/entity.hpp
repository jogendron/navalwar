#ifndef __NAVALWAR_ENTITY_HPP
#define __NAVALWAR_ENTITY_HPP

#include <memory>

#include "engine/resource_manager.hpp"

namespace Engine
{
    class Entity
    {
        public:
            Entity();
            ~Entity();

            virtual void processEvent(const SDL_Event & event);
            virtual void update();
            virtual void draw();

        protected:
            std::shared_ptr<ResourceManager> _resourceManager;
            SDL_Window * _window;
            SDL_Renderer * _renderer;
    };
}

#endif 