#pragma once
#include "Entity.hpp"
#include "Map.hpp"
#include <vector>

class Player : public Entity {
    public:
        Player();
        void SpawnIn(Map level);
        void UsedForceAt(sf::Vector2f position);
        void UpdateAnimation();
    protected:
        sf::Clock force_cooldown;
        bool alive;

};
