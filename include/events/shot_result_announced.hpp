#ifndef __BATTLESHIP_EVENTS_SHOT_RESULT_ANNOUNCED_HPP
#define __BATTLESHIP_EVENTS_SHOT_RESULT_ANNOUNCED_HPP

#include "engine/event.hpp"
#include "player_type.hpp"

#include <string>

namespace Events
{
    enum ShotResult
    {
        HIT,
        MISS,
        SUNK
    };

    class ShotResultAnnounced : public Engine::Event
    {
        public:
            ShotResultAnnounced(
                PlayerType initiator,
                const std::string & positionName, 
                ShotResult shotResult
            );
            ~ShotResultAnnounced();

            const PlayerType getInitiator() const;
            const std::string & getPositionName() const;
            const ShotResult  getShotResult() const;
            
        private:
            PlayerType _initiator;
            std::string _positionName;
            ShotResult _shotResult;
    };
}

#endif