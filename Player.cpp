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
    entity_sprite.setPosition(sf::Vector2f(level.Get_Spawn().x+8.0*Globals::SCALE,level.Get_Spawn().y+8.0*Globals::SCALE));
    entity_sprite.setOrigin(8.0,10.0);
    health.max=100;
    mana.max=100;
    speed = 400;
    rotation_speed = 350;
    max_rotation = 25;
    in_desired_position = true;
    can_control = true;
}

sf::Vector2f Player::GetPosition(){
    return  entity_sprite.getPosition();
}

void Player::SetPath(sf::Vector2f position){
    path = position;
    in_desired_position = false;
    first_move_check = true;

}

void Player::IsFalling(bool outsidemap){
    falling = outsidemap;
    if(falling)
        can_control = false;
}

sf::FloatRect Player::GetGlobalBounds(){
    return entity_sprite.getGlobalBounds();
}

void Player::Update(sf::Time time){
    if(can_control){
        if(!in_desired_position){
            //moving sprite
            sf::Vector2f movement;
            if(path.x<entity_sprite.getPosition().x)
                movement.x -=speed*time.asSeconds();
            if(path.x>entity_sprite.getPosition().x)
                movement.x +=speed*time.asSeconds();
            if(path.y<entity_sprite.getPosition().y)
                movement.y -=speed*time.asSeconds();
            if(path.y>entity_sprite.getPosition().y)
                movement.y +=speed*time.asSeconds();

            if(first_move_check){
                temp = movement;
                first_move_check = false;
            }
            //teleport,shaking fix
            if(std::abs(entity_sprite.getPosition().x-path.x)<1 || (temp.x > 0 && movement.x<0) || (temp.x < 0 && movement.x > 0)){
                entity_sprite.setPosition(path.x,entity_sprite.getPosition().y);
                movement.x = 0;
            }
            if(std::abs(entity_sprite.getPosition().y-path.y)<1 || (temp.y > 0 && movement.y<0) || (temp.y < 0 && movement.y > 0)){
                entity_sprite.setPosition(entity_sprite.getPosition().x,path.y);
                movement.y = 0;
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



            if(entity_sprite.getPosition().x == path.x  && entity_sprite.getPosition().y == path.y){
                entity_sprite.setRotation(0);
                in_desired_position = true;
                first_move_check = true;
            }
        }
    }
    else if(falling){
        entity_sprite.setRotation(0.0);
        sf::Color kolor = entity_sprite.getColor();
        kolor.a -= 1;//*time.asMilliseconds();
        sf::Vector2f Scale = entity_sprite.getScale();
        Scale.x *= 0.99;
        Scale.y *= 0.99;
        entity_sprite.setScale(Scale);
        entity_sprite.setColor(kolor );
    }
}
