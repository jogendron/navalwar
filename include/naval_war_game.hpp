#ifndef __NAVALWAR_BATTLESHIP_GAME_HPP
#define __NAVALWAR_BATTLESHIP_GAME_HPP

#include <memory>

#include "engine/game.hpp"
#include "engine/event_bus.hpp"
#include "engine/logger.hpp"

#include "player/player.hpp"

#include "events/player_ready.hpp"
#include "events/opponent_ready.hpp"
#include "events/game_started.hpp"
#include "events/game_over.hpp"
#include "events/shot_fired.hpp"
#include "events/shot_result_announced.hpp"
#include "events/new_game.hpp"

enum NavalWarGameState
{
    PRE_GAME,
    GAMING,
    POST_GAME
};

class NavalWarGame : public Engine::Game
{
    public:
        NavalWarGame();
        ~NavalWarGame();

        void processEvent(const SDL_Event & event);
        void update();
        void render();

    private:
        std::shared_ptr<Engine::EventBus> _eventBus;
        std::shared_ptr<Engine::Logger> _logger;
        
        NavalWarGameState _state;
        bool _playerIsReady;
        bool _opponentIsReady;
        bool _newGameRequested;

        std::unique_ptr<Engine::Image> _background;

        std::unique_ptr<Player::Player> _player;
        std::unique_ptr<Player::Player> _opponent;

        void initializeOpponent();

        void handlePlayerReady(std::shared_ptr<Events::PlayerReady> event);
        void handleOpponentReady(std::shared_ptr<Events::OpponentReady> event);
        void handleGameStarted(std::shared_ptr<Events::GameStarted> event);
        void handleShotFired(std::shared_ptr<Events::ShotFired> event);
        void handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event);
        void handleGameOver(std::shared_ptr<Events::GameOver> event);
        void handleNewGame(std::shared_ptr<Events::NewGame> event);

        void registerEventHandlers();
};

#endif