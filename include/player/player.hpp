#ifndef __NAVALWAR_PLAYER_PLAYER_HPP
#define __NAVALWAR_PLAYER_PLAYER_HPP

#include "engine/entity.hpp"
#include "engine/eventBus.hpp"
#include "engine/logger.hpp"

#include "player/grid.hpp"

#include "events/shot_result_announced.hpp"
#include "events/game_over.hpp"

namespace Player
{
    enum PlayerState
    {
        PLACING_SHIPS,
        READY_TO_PLAY,
        DEFENDING,
        ATTACKING,
        GAME_OVER
    };

    class Player : public Engine::Entity
    {
        public:
            Player();
            virtual ~Player();

            PlayerState getState() const;
            const int getRemainingShipsCount() const;

        protected:
            std::shared_ptr<Engine::EventBus> _eventBus;
            std::shared_ptr<Engine::Logger> _logger;

            PlayerState _state;     
            int _remainingShipsCount;

            Events::ShotResultAnnounced _lastShotResult;
            bool _needToAnnounceShotResult = false;

            void handleGameOver(std::shared_ptr<Events::GameOver> event);
    };
}

#endif
