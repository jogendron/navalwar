#ifndef __NAVALWAR_PLAYER_HUMAN_SCORE_SUMMARY_HPP
#define __NAVALWAR_PLAYER_HUMAN_SCORE_SUMMARY_HPP

#include <functional>
#include <memory>

#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "engine/font.hpp"
#include "engine/image.hpp"
#include "engine/localization.hpp"
#include "events/shot_result_announced.hpp"
#include "events/game_over.hpp"

#include "player/human/new_game_button.hpp"

namespace Player::Human
{
    class GameSummary : public Engine::Entity
    {
        public:
            GameSummary(const Engine::Resolution & currentResolution);
            ~GameSummary();

            void processEvent(const SDL_Event & event);
            void update();
            void draw();

        private:
            std::shared_ptr<Engine::EventBus> _eventBus;
            std::shared_ptr<Engine::Localization> _localization;

            Engine::Resolution _currentResolution;

            std::unique_ptr<Engine::Font> _titleFont;
            std::unique_ptr<Engine::Font> _statsFont;

            int _hitsCounter;
            int _missesCounter;
            float _precision;

            SDL_FRect _backgroundArea;
            std::shared_ptr<Engine::Image> _titleText;
            std::shared_ptr<Engine::Image> _hitsText;
            std::shared_ptr<Engine::Image> _missesText;
            std::shared_ptr<Engine::Image> _precisionText;
            std::unique_ptr<NewGameButton> _newGameButton;

            void handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event);
            void handleGameOver(std::shared_ptr<Events::GameOver> event);

            void setTitleText(std::shared_ptr<Events::GameOver> event);
            void setHitsText(std::shared_ptr<Events::GameOver> event);
            void setMissesText(std::shared_ptr<Events::GameOver> event);
            void setPrecisionText(std::shared_ptr<Events::GameOver> event);
    };
}

#endif