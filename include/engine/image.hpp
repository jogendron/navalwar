#ifndef __BATTLESHIP_ENGINE_IMAGE_HPP
#define __BATTLESHIP_ENGINE_IMAGE_HPP

#include "configuration.hpp"
#include "dimensions.hpp"
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
            Image(std::shared_ptr<SDL_Texture> texture);
            ~Image();

            Position & getPosition();
            const Dimensions & getDimensions();
            const float & getRotation() const;
            const SDL_FPoint & getRotationCenter() const;

            void setPosition(const Position & position);
            void setRotation(const float & rotation);
            void setRotationCenter(SDL_FPoint center);

            void draw();

        protected:
            std::shared_ptr<ResourceManager> _resourceManager;
            std::string _path;
            Position _position;
            Dimensions _dimensions;
            float _rotation;
            SDL_FPoint _rotationCenter;

            virtual SDL_FRect getSourceRectangle();
            virtual SDL_FRect getDestinationRectangle();

        private:
            SDL_Window * _window;
            SDL_Renderer * _renderer;
            std::shared_ptr<SDL_Texture> _texture = NULL;            
    };
}

#endif