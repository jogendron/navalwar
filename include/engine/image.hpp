#ifndef __BATTLESHIP_ENGINE_IMAGE_HPP
#define __BATTLESHIP_ENGINE_IMAGE_HPP

#include "configuration.hpp"
#include "position.hpp"
#include "resource_manager.hpp"

#include <SDL3/SDL_render.h>
#include <memory>
#include <string>

namespace Engine
{
    class Image
    {
        public:
            Image(const std::string & fileName);
            Image(
                const std::string & filename, 
                const Position & position
            );
            ~Image();

            const Position & getPosition();
            SDL_Texture * getTexture();

            void draw();

        protected:
            std::string _path;
            std::shared_ptr<ResourceManager> _resourceManager;
            Position _position;

        private:
            SDL_Window * _window;
            SDL_Renderer * _renderer;
            std::shared_ptr<SDL_Texture> _texture = NULL;
    };
}

#endif