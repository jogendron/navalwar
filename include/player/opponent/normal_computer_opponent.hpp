#ifndef __NAVALWAR_PLAYER_NORMAL_COMPUTER_OPPONENT_HPP
#define __NAVALWAR_PLAYER_NORMAL_COMPUTER_OPPONENT_HPP

#include "computer_opponent.hpp"

#include <list>

namespace Player::Opponent
{
    enum NormalComputerOpponentState
    {
        SEARCHING_SHIP,
        DISCOVERING_SHIP_ORIENTATION,
        DESTROYING_SHIP
    };

    enum OrientationDiscoveryState
    {
        CHECKING_LEFT,
        CHECKING_TOP,
        CHECKING_RIGHT,
        CHECKING_DOWN
    };

    enum TargetedShipOrientation
    {
        UNKNOWN,
        HORIZONTAL,
        VERTICAL
    };

    class NormalComputerOpponent : public ComputerOpponent
    {
        public:
            NormalComputerOpponent();
            ~NormalComputerOpponent();

        protected:
            void attack() override;
            void handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event) override;

        private:
            NormalComputerOpponentState _state;
            OrientationDiscoveryState _orientationDiscoveryState;

            std::string _firstHitPosition;
            TargetedShipOrientation _targetedShipOrientation;

            void discoverShipOrientation();
            void sinkShip();
    };
}

#endif