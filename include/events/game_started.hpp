#ifndef __NAVALWAR_EVENTS_NEWGAME_HPP
#define __NAVALWAR_EVENTS_NEWGAME_HPP

#include "engine/event.hpp"
#include "player_type.hpp"

namespace Events
{
    class GameStarted : public Engine::Event
    {
        public:
            GameStarted(PlayerType firstPlayer);
            ~GameStarted();

            PlayerType getFirstPlayer() const;

        private:
            PlayerType _firstPlayer;
    };
}

#endif