#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Globals.hpp"
#include <iostream>
#include <cstdlib>
Tile::Tile(){
}

Tile::Tile(const Tile &other){
    this->transparent = other.transparent;
    this->collide = other.collide;
    this->is_exit = other.is_exit;
    this->sprite = other.sprite;
    this->texture = other.texture;
}

void Tile::Generate(std::shared_ptr<sf::Texture> input_texture){
    input_texture->setRepeated(true);
    sprite.setTexture(*input_texture);
    sprite.scale(Globals::SCALE,Globals::SCALE);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    target.draw(sprite,states);
}

void  Tile::setPos(float x,float y){
    sprite.setPosition(x,y);
}

void Tile::Move(const sf::Vector2f &offset){
    sprite.move(offset);
}
sf::Vector2f Tile::GetPosition(){
   return sprite.getPosition();
}
sf::Vector2f Tile::GetSize(){
    sf::Vector2f size;
    size.x = sprite.getGlobalBounds().width;
    size.y  = sprite.getGlobalBounds().height;
    return size;
}
