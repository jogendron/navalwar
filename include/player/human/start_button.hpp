#ifndef __NAVALWAR_PLAYER_HUMAN_START_BUTTON_TTF
#define __NAVALWAR_PLAYER_HUMAN_START_BUTTON_TTF

#include <functional>
#include <memory>

#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "engine/font.hpp"
#include "engine/sprite.hpp"

namespace Player::Human
{
    enum StartButtonFrames
    {
        DISABLED = 0,
        ENABLED = 1
    };

    class StartButton : public Engine::Entity
    {
        public:
            StartButton(
                const Engine::Position & position,
                const Engine::Resolution & currentResolution
            );
            ~StartButton();

            bool isEnabled() const;
            void enable();
            void disable();

            void processEvent(const SDL_Event & event);
            void update();
            void draw();

        private:
            std::shared_ptr<Engine::EventBus> _eventBus;
            std::shared_ptr<Engine::Localization> _localization;

            bool _enabled = true;
            bool _clicking = false;
            bool _clicked = false;
            std::unique_ptr<Engine::Sprite> _sprite;
            std::unique_ptr<Engine::Font> _font;
            std::shared_ptr<Engine::Image> _startIdleText;
            std::shared_ptr<Engine::Image> _startClickingText;
            bool buttonWasClicked(const SDL_Event & event);
    };
}

#endif