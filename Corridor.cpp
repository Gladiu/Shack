#include "Corridor.hpp"
#include "Map.hpp"
#include <Tile.hpp>
#include <Room.hpp>
#include "Globals.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

void Corridor::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    for(auto it:Tiles)
        target.draw(it,states);
}
void Corridor::GiveTexture(sf::Texture *input_texture){
    this->texture_ptr = input_texture;
}

void Corridor::GenerateCorridor(sf::Vector2f departurepos,sf::Vector2f finalpos){
    bool generating = true;
    sf::Vector2f last_pos =departurepos;
    while(generating){
        Tile tile;
        tile.Generate(texture_ptr);
        tile.setPos(last_pos.x,last_pos.y);
        if(finalpos.x != last_pos.x){
            if(finalpos.x > last_pos.x)
                last_pos.x += Globals::SCALE*16;
            else
                last_pos.x -= Globals::SCALE*16;
        }
        else if(finalpos.y != last_pos.y){
        if(finalpos.y > last_pos.y)
            last_pos.y += Globals::SCALE*16;
        else
            last_pos.y -= Globals::SCALE*16;
        }
        else
            generating = false;
    }
}

void Corridor::SetNextLevelTrigger(bool trigger){
    this->next_level_trigger = trigger;
}

