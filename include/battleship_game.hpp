#ifndef __BATTLESHIP_BATTLESHIP_GAME_HPP
#define __BATTLESHIP_BATTLESHIP_GAME_HPP

#include <memory>

#include "engine/game.hpp"
#include "engine/eventBus.hpp"
#include "engine/logger.hpp"

#include "player/player.hpp"

#include "events/player_ready.hpp"
#include "events/opponent_ready.hpp"
#include "events/game_started.hpp"
#include "events/game_over.hpp"
#include "events/shot_fired.hpp"
#include "events/shot_result_announced.hpp"

enum BattleshipGameState
{
    PRE_GAME,
    GAMING,
    POST_GAME
};

class BattleshipGame : public Engine::Game
{
    public:
        BattleshipGame();
        ~BattleshipGame();

        void processEvent(const SDL_Event & event);
        void update();
        void render();

    private:
        std::shared_ptr<Engine::EventBus> _eventBus;
        std::shared_ptr<Engine::Logger> _logger;
        
        BattleshipGameState _state;
        bool _playerIsReady;
        bool _opponentIsReady;

        std::unique_ptr<Engine::Image> _background;

        std::unique_ptr<Player::Player> _player;
        std::unique_ptr<Player::Player> _opponent;

        void handlePlayerReady(std::shared_ptr<Events::PlayerReady> event);
        void handleOpponentReady(std::shared_ptr<Events::OpponentReady> event);
        void handleGameStarted(std::shared_ptr<Events::GameStarted> event);
        void handleShotFired(std::shared_ptr<Events::ShotFired> event);
        void handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event);
        void handleGameOver(std::shared_ptr<Events::GameOver> event);
};

#endif