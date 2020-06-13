#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Globals.hpp"
#include <iostream>
#include <cstdlib>
Tile::Tile(){
    is_exit = false;
    position = sf::Vector2f(0.0,0.0);
}

Tile::Tile(const Tile &other){
    this->is_exit = other.is_exit;
    this->sprite = other.sprite;
    this->texture = other.texture;
    this->position = other.position;
}


void Tile::Generate(std::shared_ptr<sf::Texture> input_texture){
    texture = input_texture;
    sprite.setTexture(*texture);
    sprite.scale(Globals::SCALE,Globals::SCALE);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    if(texture!=nullptr)
        target.draw(sprite,states);
}

void  Tile::setPos(float x,float y){
    sprite.setPosition(x,y);
    position.x = x;
    position.y = y;
}

void Tile::Move(const sf::Vector2f &offset){
    sprite.move(offset);
    position.x += offset.x;
    position.y += offset.y;
}
sf::Vector2f Tile::GetPosition()const{
   return sprite.getPosition();
}
sf::Vector2f Tile::GetSize(){
    sf::Vector2f size;
    size.x = sprite.getGlobalBounds().width;
    size.y  = sprite.getGlobalBounds().height;
    return size;
}
bool Tile::Overlap(const Tile& tile){
    return this->sprite.getPosition() == tile.sprite.getPosition();
}

bool Tile::GetEmpty(){
    return (texture == nullptr);
}

sf::FloatRect Tile::GetGlobalBounds(){
    return sprite.getGlobalBounds();
}

void Tile::setTextureRect(const sf::IntRect &rect){
    sprite.setTextureRect(rect);
}
sf::Color Tile::getColor(){
    return sprite.getColor();
}

void Tile::SetColor(sf::Color kolor){
    sprite.setColor(kolor);
}
