#ifndef __BATTLESHIP_PLAYER_HUMAN_SHIP_HPP
#define __BATTLESHIP_PLAYER_HUMAN_SHIP_HPP

#include <string>
#include <vector>

#include "engine/entity.hpp"
#include "engine/image.hpp"
#include "player/cell.hpp"

#include "events/shot_result_announced.hpp"

namespace Player::Human
{
    enum ShipState
    {
        IDLE,
        DRAGGING,
        DROPPING
    };

    enum ShipOrientation
    {
        HORIZONTAL,
        VERTICAL
    };

    class Ship : public Engine::Entity
    {
        public:
            Ship(const std::string & imageName, const Engine::Position & position);
            ~Ship();

            const Engine::Position & getPosition() const;
            const Engine::Dimensions & getDimensions() const;
            const ShipOrientation & getOrientation() const;

            const bool isCollisionCheckRequested() const;
            const bool collidesWith(const Ship & otherShip);
            void resetPosition();

            const bool isSnapRequested() const;
            void snap(
                const Engine::Position & position, 
                std::vector<std::reference_wrapper<Cell>> & cells
            );
            void failSnap();
            bool isOnGrid() const;

            Events::ShotResult applyShot(const std::string & positionName);
            bool isSunk() const;

            void processEvent(const SDL_Event & event) override;
            void update() override;
            void draw() override;

        private:
            Engine::Resolution _screenResolution;
            
            ShipState _state;
            ShipOrientation _orientation;
            std::unique_ptr<Engine::Image> _shipImage;
            Engine::Position _initialPosition;
            Engine::Position _position;
            Engine::Position _mousePosition;
            Engine::Position _mouseOffset;
            bool _rotationRequested;
            bool _snapRequested;
            bool _collisionCheckRequested;
            std::vector<std::reference_wrapper<Cell>> _cells;

            bool shipWasClicked(const SDL_Event & event);
            void rotate();
    };
}

#endif
