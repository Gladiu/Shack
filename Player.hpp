#pragma once
#include "Entity.hpp"
#include "Map.hpp"
#include <vector>

class Player : public Entity {
    public:
        Player(Map level);
        sf::Vector2f GetCenter();
        void SetPath(sf::Vector2f position);
        void  Update(sf::Time time);
    protected:
//        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void UpdateMovingStatus();
        bool in_desired_position;
        sf::Vector2f desired_position;
        sf::Vector2f temp;
        bool first_move_check;

};
