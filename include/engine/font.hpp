#ifndef __NAVALWAR_ENGINE_FONT_HPP
#define __NAVALWAR_ENGINE_FONT_HPP

#include "image.hpp"
#include "resource_manager.hpp"

#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <string>

#include <SDL3_ttf/SDL_ttf.h>

namespace Engine
{
    class Font
    {
        public:
            Font(const std::string & fileName, const int & size);
            ~Font();

            std::shared_ptr<Image> createImage(const std::string & text, const SDL_Color & color);

        private:
            std::shared_ptr<ResourceManager> _resourceManager;
            SDL_Renderer * _renderer;

            std::string _path;
            int _size;
            
            std::shared_ptr<TTF_Font> _font = nullptr;
    };
}

#endif