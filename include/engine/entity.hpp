#ifndef __BATTLESHIP_ENTITY_HPP
#define __BATTLESHIP_ENTITY_HPP

#include <memory>

#include "engine/resource_manager.hpp"

namespace Engine
{
    class Entity
    {
        public:
            Entity();
            ~Entity();

            virtual void update();
            virtual void draw() = 0;

        protected:
            std::shared_ptr<ResourceManager> _resourceManager;
            SDL_Window * _window;
            SDL_Renderer * _renderer;
    };
}

#endif 