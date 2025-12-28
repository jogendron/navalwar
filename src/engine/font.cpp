#include "engine/font.hpp"
#include "engine/engine.hpp"
#include <sstream>

using namespace Engine;

Font::Font(const std::string & fileName, const int & size)
: _size (size)
{
    Engine& engine = Engine::getInstance();
    
    _resourceManager = engine.getResourceManager();
    _renderer = engine.getRenderer();

    std::ostringstream oss;
    oss << "../share/" << engine.getConfiguration()->getGameName() << "/fonts/";
    oss << fileName;

    _path = oss.str();
    _font = _resourceManager->getFont(_path, _size);
}

Font::~Font()
{
}

std::shared_ptr<Image> Font::createImage(const std::string & text, const SDL_Color & color)
{
    SDL_Surface * surface = TTF_RenderText_Blended(_font.get(), text.c_str(), text.length(), color);

    std::shared_ptr<SDL_Texture> texture = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(_renderer, surface),
        [](SDL_Texture * ptr) {
            SDL_DestroyTexture(ptr);
        }
    );

    SDL_DestroySurface(surface);

    return std::make_shared<Image>(texture);
}