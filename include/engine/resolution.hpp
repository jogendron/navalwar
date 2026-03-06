#ifndef __NAVALWAR_ENGINE_RESOLUTION_HPP
#define __NAVALWAR_ENGINE_RESOLUTION_HPP

namespace Engine
{
    class Resolution
    {
        public:
            Resolution();
            Resolution(int width, int height);
            ~Resolution();
    
            const int getWidth() const;
            const int getHeight() const;
    
        private:
            static const int DEFAULT_WIDTH = 1280;
            static const int DEFAULT_HEIGHT = 720;
    
            int _width;
            int _height;
    };
}

#endif