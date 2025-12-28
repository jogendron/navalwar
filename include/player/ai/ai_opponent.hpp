#ifndef __BATTLESHIP_PLAYER_AI_OPPONENT_HPP
#define __BATTLESHIP_PLAYER_AI_OPPONENT_HPP

#include "player/player.hpp"

#include "player/cell.hpp"

#include <functional>
#include <memory>
#include <vector>

#include "events/game_started.hpp"
#include "events/shot_fired.hpp"
#include "events/shot_result_announced.hpp"

namespace Player::AI
{
    class AIOpponent : public Player::Player
    {
        public:
            AIOpponent();
            ~AIOpponent();

            void update() override;

        protected:
            std::unique_ptr<Grid> _playerGrid;
            std::unique_ptr<Grid> _opponentGrid;
            
            std::vector<std::reference_wrapper<Cell>> _carrier;
            std::vector<std::reference_wrapper<Cell>> _battleship;
            std::vector<std::reference_wrapper<Cell>> _cruiser;
            std::vector<std::reference_wrapper<Cell>> _submarine;
            std::vector<std::reference_wrapper<Cell>> _destroyer;
            
            virtual void attack() = 0;

        private:
            void placeShips();
            void placeShip(std::vector<std::reference_wrapper<Cell>> & ship, int shipLength);

            void handleGameStarted(std::shared_ptr<Events::GameStarted> event);
            void handleShotFired(std::shared_ptr<Events::ShotFired> event); 
            void handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event);     

            Events::ShotResult applyShotFired(
                std::vector<std::reference_wrapper<Cell>> & ship,
                std::shared_ptr<Events::ShotFired> event
            );
    };
}

#endif
