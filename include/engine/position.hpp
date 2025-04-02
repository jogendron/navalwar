#ifndef __BATTLESHIP_ENGINE_POSITION_HPP
#define __BATTLESHIP_ENGINE_POSITION_HPP

namespace Engine
{
    class Position
    {
        public:
            Position();
            Position(float x, float y);
            ~Position();

            const float & getX() const;
            const float & getY() const;

            void setX(const float & value);
            void setY(const float & value);
        
        private:
            float _x;
            float _y;
    };
}

#endif