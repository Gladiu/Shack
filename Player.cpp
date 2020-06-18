#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "Player.hpp"
#include "Map.hpp"
#include "Globals.hpp"

Player::Player(){
    std::cout<<"Loading Player assets..."<<std::endl;
    texture.loadFromFile("textures/hero.png",sf::IntRect(0, 0, 3*16, 4*16));
    entity_sprite.setTextureRect(sf::IntRect(0,0,16,16));
    texture.generateMipmap();
    entity_sprite.setTexture(this->texture);
    entity_sprite.setScale(Globals::SCALE/1.25,Globals::SCALE/1.25);
    texture.setRepeated(true);
    entity_sprite.setOrigin(8.0,10.0);
    health.max=100;
    mana.max=100;
    speed = 500;
    rotation_speed = 350;
    max_rotation = 25;
    monster = false;
    push_factor = 1;
}

void Player::SpawnIn(Map level){
    entity_sprite.setPosition(sf::Vector2f(level.Get_Spawn().x+8.0*Globals::SCALE,level.Get_Spawn().y+8.0*Globals::SCALE));
}

void Player::UsedForceAt(sf::Vector2f position){
    sf::IntRect rect = entity_sprite.getTextureRect();
    if(position.x >= entity_sprite.getPosition().x){
        rect.left = 16.0;
        rect.top = 16.0;
    }
    else{
        rect.top = 0.0;
        rect.left = 16.0;
    }
    entity_sprite.setTextureRect(rect);
    force_cooldown.restart();

}

void Player::UpdateAnimation(){
    if(force_cooldown.getElapsedTime().asSeconds()>.5){
            sf::IntRect rect = entity_sprite.getTextureRect();
            rect.left =0;
            entity_sprite.setTextureRect(rect);
    }
}
