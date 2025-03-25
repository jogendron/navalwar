#ifndef __BATTLESHIP_ENGINE_RESOURCE_MANAGER_HPP
#define __BATTLESHIP_ENGINE_RESOURCE_MANAGER_HPP

#include <map>
#include <memory>
#include <string>

#include <SDL3/SDL_render.h>

namespace Engine
{
    class ResourceManager
    {
        public:
            ResourceManager(SDL_Renderer * renderer);
            ~ResourceManager();

            std::shared_ptr<SDL_Texture> getTexture(const std::string & path);

        private:
            SDL_Renderer * _renderer;
            std::map<std::string, std::shared_ptr<SDL_Texture>> _textures;
    };
}

#endif