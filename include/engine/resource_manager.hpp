#ifndef __NAVALWAR_ENGINE_RESOURCE_MANAGER_HPP
#define __NAVALWAR_ENGINE_RESOURCE_MANAGER_HPP

#include <map>
#include <memory>
#include <string>

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace Engine
{
    class ResourceManager
    {
        public:
            ResourceManager(SDL_Renderer * renderer);
            ~ResourceManager();

            std::shared_ptr<SDL_Texture> getTexture(const std::string & path);
            std::shared_ptr<TTF_Font> getFont(const std::string & path, const int & size);

            void clear();

        private:
            SDL_Renderer * _renderer;
            std::map<std::string, std::shared_ptr<SDL_Texture>> _textures;
            std::map<std::string, std::shared_ptr<TTF_Font>> _fonts;
    };
}

#endif