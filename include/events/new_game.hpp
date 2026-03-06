#ifndef __NAVALWAR_EVENTS_NEW_GAME_HPP
#define __NAVALWAR_EVENTS_NEW_GAME_HPP

#include "engine/event.hpp"

namespace Events
{
    class NewGame : public Engine::Event
    {
        public:
            NewGame();
            ~NewGame();
            
        private:
    };
}

#endif
