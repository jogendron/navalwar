#ifndef __NAVALWAR_PLAYER_HUMAN_NEW_GAME_BUTTON_HPP
#define __NAVALWAR_PLAYER_HUMAN_NEW_GAME_BUTTON_HPP

#include <functional>
#include <memory>

#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "engine/font.hpp"
#include "engine/image.hpp"
#include "engine/localization.hpp"

namespace Player::Human
{
    class NewGameButton : public Engine::Entity
    {
        public:
            NewGameButton(const Engine::Resolution & currentResolution);
            ~NewGameButton();

            void processEvent(const SDL_Event & event);
            void update();
            void draw();

        private:
            std::shared_ptr<Engine::EventBus> _eventBus;
            std::shared_ptr<Engine::Localization> _localization;

            std::unique_ptr<Engine::Image> _background;
            std::unique_ptr<Engine::Font> _font;
            std::shared_ptr<Engine::Image> _text;

            bool _clicking;
            bool _clicked;
            bool buttonWasClicked(const SDL_Event & event);
    };
}

#endif