#ifndef __NAVALWAR_EVENTS_SHOT_FIRED_HPP
#define __NAVALWAR_EVENTS_SHOT_FIRED_HPP

#include "engine/event.hpp"
#include "player_type.hpp"

#include <string>

namespace Events
{
    class ShotFired : public Engine::Event
    {
        public:
            ShotFired(PlayerType initiator, const std::string & positionName);
            ~ShotFired() override;

            const PlayerType getInitiator() const;
            const std::string & getPositionName() const;

        private:
            PlayerType _initiator;
            std::string _positionName;
    };
}

#endif