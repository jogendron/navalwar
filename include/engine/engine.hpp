#ifndef __BATTLESHIP_ENGINE_ENGINE_HPP
#define __BATTLESHIP_ENGINE_ENGINE_HPP

#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>

#include "engine/configuration.hpp"
#include "engine/eventBus.hpp"
#include "engine/game.hpp"
#include "engine/logger.hpp"
#include "engine/resource_manager.hpp"

namespace Engine
{
    class Engine
    {
        public:
            ~Engine();

            static void init(int argc, char * argv[]);
            static void quit();
            static Engine & getInstance();

            SDL_Window * getWindow();
            SDL_Renderer * getRenderer();
            std::shared_ptr<Configuration> getConfiguration();
            std::shared_ptr<EventBus> getEventBus();
            std::shared_ptr<Logger> getLogger();
            std::shared_ptr<ResourceManager> getResourceManager();
            Uint64 getTicks();

            void run(const std::shared_ptr<Game> game);

        private:
            Engine();

            SDL_Window * _window = 0;
            SDL_Renderer * _renderer = 0;
            std::shared_ptr<Configuration> _configuration;
            std::shared_ptr<EventBus> _eventBus;
            std::shared_ptr<Logger> _logger;
            std::shared_ptr<ResourceManager> _resourceManager;

            void setLogLevel(const std::string & logLevel);
    };
}

#endif