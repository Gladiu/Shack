#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Globals.hpp"
#include <iostream>
#include <cstdlib>
Tile::Tile(){

}

void Tile::Generate(int input,sf::Texture *input_texture){
    this->type = static_cast<Tile_Type>(input);
/*    switch(type){
        case floor:
            this->texture.loadFromFile("textures/floor.png");
            break;
    }*/
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
