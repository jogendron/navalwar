#ifndef __NAVALWAR_PLAYER_COMPUTER_OPPONENT_HPP
#define __NAVALWAR_PLAYER_COMPUTER_OPPONENT_HPP

#include "player/player.hpp"

#include "player/cell.hpp"

#include <functional>
#include <memory>
#include <vector>

#include "events/game_started.hpp"
#include "events/shot_fired.hpp"
#include "events/shot_result_announced.hpp"

namespace Player::Opponent
{
    class ComputerOpponent : public Player::Player
    {
        public:
            ComputerOpponent();
            ~ComputerOpponent();

            void update() override;

        protected:
            std::unique_ptr<Grid> _playerGrid;
            std::unique_ptr<Grid> _opponentGrid;
            
            std::vector<std::reference_wrapper<Cell>> _carrier;
            std::vector<std::reference_wrapper<Cell>> _battleship;
            std::vector<std::reference_wrapper<Cell>> _cruiser;
            std::vector<std::reference_wrapper<Cell>> _submarine;
            std::vector<std::reference_wrapper<Cell>> _destroyer;
            
            virtual void handleGameStarted(std::shared_ptr<Events::GameStarted> event);
            virtual void handleShotFired(std::shared_ptr<Events::ShotFired> event); 
            virtual void handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event);     

            void attackRandomCell();
            void attackCell(const std::string & positionName);

            virtual void attack() = 0;

        private:
            void placeShips();
            void placeShip(std::vector<std::reference_wrapper<Cell>> & ship, int shipLength);

            Events::ShotResult applyShotFired(
                std::vector<std::reference_wrapper<Cell>> & ship,
                std::shared_ptr<Events::ShotFired> event
            );
    };
}

#endif
