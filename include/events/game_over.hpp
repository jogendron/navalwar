#ifndef __NAVALWAR_EVENTS_GAMEOVER_HPP
#define __NAVALWAR_EVENTS_GAMEOVER_HPP

#include "engine/event.hpp"
#include "player_type.hpp"

namespace Events
{
    class GameOver : public Engine::Event
    {
        public:
            GameOver(PlayerType winner);
            ~GameOver();

            PlayerType getWinner() const;
            
        private:
            PlayerType _winner;
    };
}

#endif