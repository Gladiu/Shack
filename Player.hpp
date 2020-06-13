#pragma once
#include "Entity.hpp"
#include "Map.hpp"
#include "Monster.hpp"
#include <vector>

class Player : public Entity {
    public:
        Player(Map level);
        sf::Vector2f GetPosition();
        void SetPath(const sf::Vector2f & position);
        void  Update(sf::Time time);
        void IsFalling(bool outsidemap);
        sf::FloatRect GetGlobalBounds();
        void Interact(Monster monster);
    protected:
        void UpdateMovingStatus();
        bool can_control;
        bool falling;
        bool in_desired_position;
        sf::Vector2f desired_position;
        sf::Vector2f temp;
        bool first_move_check;
        sf::Vector2f path;

};
