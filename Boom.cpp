#include "Boom.hpp"
#include "Globals.hpp"
#include <iostream>

Boom::Boom(){
    speed = 300;
    rotation_speed = 200;
    max_rotation = 25;
    monster = true;
    progressing_animation = true;
    movable = false;
    push_factor = 1;

}

void Boom::SetPosition(sf::Vector2f position){
    entity_sprite.setPosition(position);
}

void Boom::SetTexture(const std::shared_ptr<sf::Texture> &texture_ptr){
    entity_texture = texture_ptr;
    entity_sprite.setTexture(*entity_texture);
    entity_sprite.setTextureRect(sf::IntRect(0,0,16.0,16.0));
    entity_sprite.setScale(Globals::SCALE,Globals::SCALE);
    entity_sprite.setOrigin(8.0,8.0);
}

