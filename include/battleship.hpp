#ifndef __BATTLESHIP_BATTLESHIP_HPP
#define __BATTLESHIP_BATTLESHIP_HPP

#include "ship.hpp"

class Battleship : public Ship
{
    public:
        Battleship(const Engine::Position & position);
        ~Battleship();

    private:
};

#endif