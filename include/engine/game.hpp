#ifndef __BATTLESHIP_ENGINE_GAME_HPP
#define __BATTLESHIP_ENGINE_GAME_HPP

#include "configuration.hpp"
#include "image.hpp"
#include "resource_manager.hpp"

#include <memory>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

namespace Engine
{
    class Game
    {
        public:
            Game();
            virtual ~Game() = default;
    
            virtual void processEvent(const SDL_Event & event) = 0;
            virtual void update() = 0;
            virtual void render() = 0;
    
        protected:
            std::shared_ptr<Configuration> _configuration;
            std::shared_ptr<ResourceManager> _resourceManager;
            SDL_Window * _window;
            SDL_Renderer * _renderer;
    };
}

#endif