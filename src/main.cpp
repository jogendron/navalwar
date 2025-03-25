#include <memory>

#include "engine/engine.hpp"
#include "battleship_game.hpp"

int main(int argc, char * argv[])
{
    int rv = 0;
    std::shared_ptr<Engine::Game> game = 0;

    try
    {
        Engine::Engine::init(argc, argv);
        game = std::make_shared<BattleshipGame>();
        
        Engine::Engine::getInstance().run(game);
    }
    catch(const std::exception & e)
    {
        rv = 1;
    }
    
    Engine::Engine::quit();
    return rv;
}