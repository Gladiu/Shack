#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.hpp"
#include "Map.hpp"
#include "Globals.hpp"

Player::Player(Map level){
    std::cout<<"Loading Player assets..."<<std::endl;
    entity_texture.loadFromFile("textures/hero.png",sf::IntRect(0, 0, 16, 16));
    entity_sprite.setTexture(this->entity_texture);
    entity_sprite.setScale(Globals::SCALE/1.5,Globals::SCALE/1.5);
    entity_sprite.setPosition(level.Get_Spawn());
    entity_sprite.setOrigin(8.0,8.0);
    health.max=100;
    mana.max=100;
    speed = 5;
    in_desired_position = true;
}

sf::Vector2f Player::GetCenter(){
    sf::Vector2f buffor = entity_sprite.getPosition();
    buffor.x+=0;
    buffor.y+=0;
    return buffor;
}

void Player::SetPath(sf::Vector2f position){
    desired_position = position;
    in_desired_position = false;
    std::cout<<desired_position.x<<desired_position.y<<std::endl;
}

void Player::Update(sf::Time time){
    if(!in_desired_position){
        std::cout<<time.asMilliseconds()<<std::endl;
        sf::Vector2f movement;
        if(desired_position.x<entity_sprite.getPosition().x)
            movement.x -=speed*time.asMilliseconds();
        if(desired_position.x>entity_sprite.getPosition().x)
            movement.x +=speed*time.asMilliseconds();
        if(desired_position.y<entity_sprite.getPosition().y)
            movement.y -=speed*time.asMilliseconds();
        if(desired_position.y>entity_sprite.getPosition().y)
            movement.y +=speed*time.asMilliseconds();
        if(desired_position == entity_sprite.getPosition()){
            in_desired_position = true;
        }
        entity_sprite.move(movement);
    }
}
