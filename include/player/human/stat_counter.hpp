#ifndef __BATTLESHIP_PLAYER_HUMAN_GAMEPANEL_HPP
#define __BATTLESHIP_PLAYER_HUMAN_GAMEPANEL_HPP

#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "engine/eventBus.hpp"
#include "engine/font.hpp"
#include "engine/image.hpp"
#include "engine/localization.hpp"
#include "events/shot_result_announced.hpp"

#include <memory>

namespace Player::Human
{
    class StatCounter : public Engine::Entity
    {
        public:
            StatCounter(
                const Engine::Position & position,
                const Engine::Resolution & currentResolution
            );
            ~StatCounter();

            void update();
            void draw();
            
        private:
            std::shared_ptr<Engine::EventBus> _eventBus;
            std::shared_ptr<Engine::Localization> _localization;
            std::unique_ptr<Engine::Font> _font;

            bool _playerChanged;
            int _playerShipsLeft;
            std::unique_ptr<Engine::Image> _playerPanelBackground;
            std::shared_ptr<Engine::Image> _playerText;
            
            bool _opponentChanged;
            int _opponentShipsLeft;
            std::unique_ptr<Engine::Image> _opponentPanelBackground;
            std::shared_ptr<Engine::Image> _opponentText;
            
            std::shared_ptr<Engine::Image> createShipsLeftText(int shipsLeft) const;
            void handleShotResultAnnounced(std::shared_ptr<Events::ShotResultAnnounced> event);
    };
};

#endif