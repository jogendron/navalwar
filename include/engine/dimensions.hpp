#ifndef __BATTLESHIP_ENGINE_DIMENSIONS_HPP
#define __BATTLESHIP_ENGINE_DIMENSIONS_HPP

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

        private:
            int _width;
            int _height;
    };
}

#endif