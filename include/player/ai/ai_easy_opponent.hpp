#ifndef __NAVALWAR_PLAYER_AI_EASY_OPPONENT_HPP
#define __NAVALWAR_PLAYER_AI_EASY_OPPONENT_HPP

#include "ai_opponent.hpp"

namespace Player::AI
{
    class AIEasyOpponent : public AIOpponent
    {
        public:
            AIEasyOpponent();
            ~AIEasyOpponent();

        protected:
            void attack() override;

        private:
    };
}

#endif
