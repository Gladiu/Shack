#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "Player.hpp"
#include "Map.hpp"
#include "Globals.hpp"

Player::Player(Map level){
    std::cout<<"Loading Player assets..."<<std::endl;
    entity_texture.loadFromFile("textures/hero.png",sf::IntRect(0, 0, 5*16, 16));
    entity_sprite.setTextureRect(sf::IntRect(0,0,16,16));
    entity_texture.generateMipmap();
    entity_sprite.setTexture(this->entity_texture);
    entity_sprite.setScale(Globals::SCALE/1.5,Globals::SCALE/1.5);
    entity_texture.setRepeated(true);
    entity_sprite.setPosition(level.Get_Spawn());
    entity_sprite.setOrigin(8.0,10.0);
    health.max=100;
    mana.max=100;
    speed = 400;
    rotation_speed = 350;
    max_rotation = 25;
    in_desired_position = true;
}

sf::Vector2f Player::GetCenter(){
    sf::Vector2f buffor = entity_sprite.getPosition();
    buffor.x+=0;
    buffor.y+=0;
    return buffor;
}

void Player::SetPath(sf::Vector2f position){
    //introduce path finding alghoritm in future
    desired_position = position;
    in_desired_position = false;
    first_move_check = true;

}

void Player::Update(sf::Time time){
    if(!in_desired_position){
        //moving sprite
        sf::Vector2f movement;
        if(desired_position.x<entity_sprite.getPosition().x)
            movement.x -=speed*time.asSeconds();
        if(desired_position.x>entity_sprite.getPosition().x)
            movement.x +=speed*time.asSeconds();
        if(desired_position.y<entity_sprite.getPosition().y)
            movement.y -=speed*time.asSeconds();
        if(desired_position.y>entity_sprite.getPosition().y)
            movement.y +=speed*time.asSeconds();
        if(desired_position == entity_sprite.getPosition()){
            in_desired_position = true;
        }

        if(first_move_check){
            temp = movement;
            first_move_check = false;
        }
        //teleport,shaking fix
        if(std::abs(entity_sprite.getPosition().x-desired_position.x)<1)
            entity_sprite.setPosition(desired_position.x,entity_sprite.getPosition().y);
        if(std::abs(entity_sprite.getPosition().y-desired_position.y)<1)
            entity_sprite.setPosition(entity_sprite.getPosition().x,desired_position.y);
        if(std::abs(entity_sprite.getPosition().x-desired_position.x) == 0 && std::abs(entity_sprite.getPosition().y-desired_position.y) == 0){
            in_desired_position = true;
            entity_sprite.setRotation(0);
        }

        //walking animation
        if(entity_sprite.getRotation() >=(max_rotation) && entity_sprite.getRotation() <=(360-max_rotation))
            rotation_speed = -rotation_speed;
        //moving eyes in direction of walking
        if(temp.x>=0)
            entity_sprite.setTextureRect(sf::IntRect(3*16,0,16,16));
        else
            entity_sprite.setTextureRect(sf::IntRect(0,0,16,16));

        //moving and rotating sprite;
        entity_sprite.rotate(time.asSeconds()*rotation_speed);
        entity_sprite.move(movement);

    }

}
