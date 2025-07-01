#ifndef __BATTLESHIP_CARRIER_HPP
#define __BATTLESHIP_CARRIER_HPP

#include "ship.hpp"

class Carrier : public Ship
{
    public:
        Carrier(const Engine::Position & position);
        ~Carrier();
    
    private:
};

#endif