#include "engine/resource_manager.hpp"
#include "engine/path_factory.hpp"

#include <SDL3_image/SDL_image.h>

using namespace Engine;

ResourceManager::ResourceManager(SDL_Renderer * renderer)
: _renderer (renderer)
{
}

ResourceManager::~ResourceManager()
{
    // renderer will be freed by main
}

std::shared_ptr<SDL_Texture> ResourceManager::getTexture(const std::string & path)
{
    std::shared_ptr<SDL_Texture> texture = NULL;
    std::map<std::string, std::shared_ptr<SDL_Texture>>::iterator it = _textures.find(path);

    if (it == _textures.end())
    {
        texture = std::shared_ptr<SDL_Texture>(
            IMG_LoadTexture_IO(_renderer, SDL_IOFromFile(PathFactory::createPath(path).c_str(), "r"), true), 
            [](SDL_Texture * ptr) {
                SDL_DestroyTexture(ptr);
            }
        );
        _textures.insert({path, texture});
    }
    else
    {
        texture = it->second;
    }

    return texture;
}

std::shared_ptr<TTF_Font> ResourceManager::getFont(const std::string & path, const int & size)
{
    std::shared_ptr<TTF_Font> font = NULL;
    std::string key = path + "-" + std::to_string(size);
    std::map<std::string, std::shared_ptr<TTF_Font>>::iterator it = _fonts.find(key);
    
    if (it == _fonts.end())
    {
        font = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(PathFactory::createPath(path).c_str(), size), 
            [](TTF_Font * ptr) {
                TTF_CloseFont(ptr);
            }
        );

        if (! font)
        {
            
        }

        _fonts.insert({key, font});
    }
    else
    {
        font = it->second;
    }

    return font;
}

void ResourceManager::clear()
{
    _textures.clear();
    _fonts.clear();
}