#ifndef __NAVALWAR_EVENTS_OPPONENT_READY_HPP
#define __NAVALWAR_EVENTS_OPPONENT_READY_HPP

#include "engine/event.hpp"

namespace Events
{
    class OpponentReady : public Engine::Event
    {
        public:
            OpponentReady();
            ~OpponentReady();
    };
}

#endif