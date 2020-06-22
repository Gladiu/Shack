#pragma once
#include "Entity.hpp"
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>


class Boom : public Entity{
public:
    Boom();
    void SetPosition(sf::Vector2f position);
    void SetTexture(const std::shared_ptr<sf::Texture> & texture_ptr);
protected:
    bool progressing_animation;
};


