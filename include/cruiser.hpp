#ifndef __BATTLESHIP_CRUISER_HPP
#define __BATTLESHIP_CRUISER_HPP

#include "ship.hpp"

class Cruiser : public Ship
{
    public:
        Cruiser(const Engine::Position & position);
        ~Cruiser();
    
    private:
};

#endif