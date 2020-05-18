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
    in_move = false;
}

//void Player::draw(sf::RenderTarget& target, sf::RenderStates states)const{
//    target.draw(entity_sprite,states);
//}

void Player::Update(){
//sf::Event user_event;
}

sf::Vector2f Player::GetCenter(){
    sf::Vector2f buffor = entity_sprite.getPosition();
    buffor.x+=0;
    buffor.y+=0;
    return buffor;
}
void Player::UpdateMovingStatus(){
    if(in_move)
        in_move=false;
    else
        in_move=true;
}

bool Player::IsMoving(){
    return in_move;
}

void Player::Interact(Map level){
//    this->UpdateMovingStatus();
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !in_move){
    path = level.Generate_Path(entity_sprite.getPosition());
    }

}
