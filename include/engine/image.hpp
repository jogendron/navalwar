#ifndef __BATTLESHIP_ENGINE_IMAGE_HPP
#define __BATTLESHIP_ENGINE_IMAGE_HPP

#include "configuration.hpp"
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
            ~Image();

            SDL_Texture * getTexture();

        protected:
            std::string _path;
            std::shared_ptr<ResourceManager> _resourceManager;

        private:
            std::shared_ptr<SDL_Texture> _texture = NULL;
    };
}

#endif