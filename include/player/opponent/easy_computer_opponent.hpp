#ifndef __NAVALWAR_PLAYER_EASY_COMPUTER_OPPONENT_HPP
#define __NAVALWAR_PLAYER_EASY_COMPUTER_OPPONENT_HPP

#include "computer_opponent.hpp"

namespace Player::Opponent
{
    class EasyComputerOpponent : public ComputerOpponent
    {
        public:
            EasyComputerOpponent();
            ~EasyComputerOpponent();

        protected:
            void attack() override;

        private:
    };
}

#endif
