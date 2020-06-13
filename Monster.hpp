#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
class Monster : public Entity{
    public:
        void Update(sf::Time time);
};
