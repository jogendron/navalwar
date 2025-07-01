#ifndef __BATTLESHIP_SUBMARINE_HPP
#define __BATTLESHIP_SUBMARINE_HPP

#include "ship.hpp"

class Submarine : public Ship
{
    public:
        Submarine(const Engine::Position & position);
        ~Submarine();
    
    private:
};

#endif