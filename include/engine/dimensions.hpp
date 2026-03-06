#ifndef __NAVALWAR_ENGINE_DIMENSIONS_HPP
#define __NAVALWAR_ENGINE_DIMENSIONS_HPP

#include "engine/resolution.hpp"

namespace Engine
{
    class Dimensions
    {
        public:
            Dimensions();
            Dimensions(int width, int height);
            ~Dimensions();

            const int getWidth() const;
            const int getHeight() const;

            Dimensions scale(const Resolution& from, const Resolution& to) const;

        private:
            int _width;
            int _height;
    };
}

#endif