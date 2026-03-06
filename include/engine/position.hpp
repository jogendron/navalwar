#ifndef __NAVALWAR_ENGINE_POSITION_HPP
#define __NAVALWAR_ENGINE_POSITION_HPP

#include "engine/resolution.hpp"

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

            Position scale(const Resolution& from, const Resolution& to) const;
        
        private:
            float _x;
            float _y;
    };
}

#endif