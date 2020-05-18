#pragma once
#include "Entity.hpp"
#include "Map.hpp"
#include <vector>

class Player : public Entity {
    public:
        Player(Map level);
        void Update();
        sf::Vector2f GetCenter();
        void Interact(Map level);
        bool IsMoving();
    protected:
//        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void UpdateMovingStatus();
        bool in_move;
        std::vector<sf::Vector2f> path;
};
