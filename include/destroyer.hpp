#ifndef __BATTLESHIP_DESTROYER_HPP
#define __BATTLESHIP_DESTROYER_HPP

#include "ship.hpp"

class Destroyer : public Ship
{
    public:
        Destroyer(const Engine::Position & position);
        ~Destroyer();
        
    private:
};

#endif