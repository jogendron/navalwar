#ifndef __NAVALWAR_SPRITE_HPP
#define __NAVALWAR_SPRITE_HPP

#include <string>
#include <vector>

#include "configuration.hpp"
#include "dimensions.hpp"
#include "image.hpp"
#include "position.hpp"
#include "resource_manager.hpp"

namespace Engine
{

    class Sprite : public Image
    {
        public:
            Sprite(
                const std::string & fileName,
                const Dimensions & frameDimensions,
                const std::vector<Position> & frames
            );
            Sprite(
                const std::string & filename, 
                const Position & position,
                const Dimensions & frameDimensions,
                const std::vector<Position> & frames
            );
            ~Sprite();

            const size_t getCurrentFrameIndex() const;
            void setCurrentFrameIndex(size_t index);

        private:
            Dimensions _frameDimensions;
            std::vector<Position> _frames;
            size_t _currentFrameIndex;

            SDL_FRect getSourceRectangle() override;
            SDL_FRect getDestinationRectangle() override;
    };

}

#endif