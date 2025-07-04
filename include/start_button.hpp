#ifndef __BATTLESHIP_START_BUTTON
#define __BATTLESHIP_START_BUTTON

#include <functional>
#include <memory>

#include "engine/entity.hpp"
#include "engine/sprite.hpp"

enum StartButtonFrames
{
    DISABLED = 0,
    ENABLED = 1,
    CLICKING = 2
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

        std::function<void()> onClick;

    private:
        bool _enabled = true;
        bool _clicked = false;
        std::unique_ptr<Engine::Sprite> _sprite;

        bool buttonWasClicked(const SDL_Event & event);
};

#endif