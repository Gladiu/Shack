#include "Robot.hpp"
#include "Globals.hpp"
#include <iostream>

Robot::Robot(){
    speed = 300;
    rotation_speed = 160;
    max_rotation = 25;
    monster = true;
    progressing_animation = true;
    movable = true;
    push_factor = 5;
}

void Robot::SetPosition(sf::Vector2f position){
    entity_sprite.setPosition(position);
}

void Robot::SetTexture(const std::shared_ptr<sf::Texture> &texture_ptr){
    entity_texture = texture_ptr;
    entity_sprite.setTexture(*entity_texture);
    entity_sprite.setTextureRect(sf::IntRect(0,0,16.0,16.0));
    entity_sprite.setScale(Globals::SCALE,Globals::SCALE);
    entity_sprite.setOrigin(8.0,8.0);
}

