#pragma once
#include <SFML/Audio.hpp>
#include "Entity.hpp"


class Robot:public Entity{
public:
    Robot();
    void SetPosition(sf::Vector2f position);
    void SetTexture(const std::shared_ptr<sf::Texture> & texture_ptr);
protected:
    bool progressing_animation;

};


