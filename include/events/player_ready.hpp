#ifndef __NAVALWAR_EVENTS_PLAYER_READY_HPP
#define __NAVALWAR_EVENTS_PLAYER_READY_HPP

#include "engine/event.hpp"

namespace Events
{
    class PlayerReady : public Engine::Event
    {
        public:
            PlayerReady();
            ~PlayerReady();
    };
}

#endif