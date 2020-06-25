#include "Corridor.hpp"
#include "Tile.hpp"
#include "Room.hpp"
#include "Globals.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

void Corridor::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    for(auto it:Tiles)
        target.draw(it,states);
}
void Corridor::GiveTexture(std::shared_ptr<sf::Texture> input_texture){
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
        if(finalpos == last_pos)
            generating = false;
        Tiles.emplace_back(tile);
    }

}

void Corridor::SetNextLevelTrigger(bool trigger){
    this->next_level_trigger = trigger;
}

bool Corridor::WillCollide(int direction, int lenght,const sf::Vector2f position){
    bool colliding = false;
    sf::Vector2f temp_position = position;
    int temp_adding = 0;
    for(auto it : Tiles){
        temp_position = position;
        sf::Vector2f tile_position = it.GetPosition();
        if(colliding)
            break;
        while(!colliding && temp_adding <lenght){
            switch(direction){
                case 0:
                    temp_position.y -= Globals::SCALE*16;
                    break;
                case 1:
                    temp_position.x -= Globals::SCALE*16;
                    break;
                case 2:
                    temp_position.y += Globals::SCALE*16;
                    break;
                case 3:
                    temp_position.x += Globals::SCALE*16;
                    break;
            }
            if(((temp_position.x >= tile_position.x && tile_position.x+Globals::SCALE*16 >= temp_position.x)
                || (temp_position.x <= tile_position.x && tile_position.x <= temp_position.x+Globals::SCALE*16))
                &&((temp_position.y >= tile_position.y && tile_position.y+Globals::SCALE*16 >= temp_position.y)
                || (temp_position.y <= tile_position.y && tile_position.y <= temp_position.y+Globals::SCALE*16)))
                colliding = true;
        }
    }
    return colliding;
}

const sf::Vector2f Corridor::Get_Top_Left_Corner() const{
    sf::Vector2f buffer = Tiles[0].GetPosition();
    for(auto &it:Tiles){
        if( buffer.x > it.GetPosition().x || buffer.y > it.GetPosition().y )
            buffer = it.GetPosition();
    }
    return buffer;
}

const std::vector<Tile> &Corridor::GetTiles() const{
    return Tiles;
}
