#ifndef __BATTLESHIP_PLAYER_HUMAN_HUMAN_PLAYER_HPP
#define __BATTLESHIP_PLAYER_HUMAN_HUMAN_PLAYER_HPP

#include "player/player.hpp"
#include "player/human/human_grid.hpp"
#include "player/human/start_button.hpp"
#include "events/game_started.hpp"
#include "events/shot_fired.hpp"
#include "events/shot_result_announced.hpp"

namespace Player::Human
{
    class HumanPlayer : public Player::Player
    {
        public:
            HumanPlayer();
            ~HumanPlayer() override;

            void processEvent(const SDL_Event & event) override;
            void update() override;
            void draw() override;

        private:
            HumanGrid * _humanPlayerGrid;
            std::array<std::shared_ptr<Ship>, 5> _ships;
            std::unique_ptr<StartButton> _startButton;

            void processShipEvent(const SDL_Event & event);
            void processStartButtonEvent(const SDL_Event & event);
            void processAttackEvents(const SDL_Event & event);

            void updateShips();
            void updateStartButton();

            bool allShipsOnGrid() const;

            void handleGameStarted(std::shared_ptr<Events::GameStarted> event);
            void handleShotFired(std::shared_ptr<Events::ShotFired> event);
            void handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event);
    };
}

#endif
