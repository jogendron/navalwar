#include <iostream>
#include <memory>

#include "engine/engine.hpp"
#include "naval_war_game.hpp"

int main(int argc, char * argv[])
{
    int rv = 0;
    std::shared_ptr<Engine::Game> game = nullptr;

    try
    {
        Engine::Engine::init(argc, argv, "navalwar");
        game = std::make_shared<NavalWarGame>();
        
        Engine::Engine::getInstance().run(game);
    }
    catch(const std::exception & e)
    {
        rv = 1;
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    
    return rv;
}