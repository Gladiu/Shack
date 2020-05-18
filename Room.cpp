#include "Room.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include "Globals.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
Room::Room(){
}



void Room::Generate(sf::Texture *input_texture){


    //generating dimensions of room
    this->size.y  = 16.0 * Globals::SCALE*(std::rand()%9+2);
    this->size.x = 16.0 * Globals::SCALE*(std::rand()%9+2);
    this->top_left_pos.x=std::rand()%10*16.0*Globals::SCALE;
    this->top_left_pos.y=std::rand()%10*16.0*Globals::SCALE;

    //filling room with floor tiles
    bool generating=true;
    sf::Vector2f last_tile_pos;
    last_tile_pos.x=0.0;
    last_tile_pos.y=0.0;
    while(generating){
        Tile generated_tile;
        generated_tile.Generate(0,input_texture);
        generated_tile.setPos(top_left_pos.x+last_tile_pos.x,
                        top_left_pos.y+last_tile_pos.y);

        if(last_tile_pos.x < this->size.y)
            last_tile_pos.x += 16.0*Globals::SCALE;
        if(last_tile_pos.x >= this->size.y){
            last_tile_pos.x = 0;
            last_tile_pos.y += 16.0*Globals::SCALE;
            }
        if(last_tile_pos.y >= this->size.x)
            generating = false;

        Tiles.emplace_back(generated_tile);
    }
    std::cout<<"w: "<<this->size.y/(16*Globals::SCALE);
    std::cout<<" h: "<<this->size.x/(16*Globals::SCALE)<<std::endl;

}

void Room::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    for(auto it:Tiles)
        target.draw(it,states);
}

sf::Vector2f Room::Get_Top_Left_Corner(){
    return top_left_pos;
}

bool Room::Collision_Check(Room another_room){
    //huge ass check if two rooms overlap and if they do move them so they dont
    //looks terriible but its just comparing 4 floats hidden in sf::Vector2f
    //if two rooms overlap something here is wrong
    //ANY CHANGES HERE MUST BE CHANGED IN VOID OVERLAP_FIX AS WELL
    //WORST CASE IT WONT GENERATE ROOMS AT ALL
    //todo: fix
    if(((this->top_left_pos.x <= another_room.top_left_pos.x && this->top_left_pos.x+this->size.x >= another_room.top_left_pos.x)
        || (another_room.top_left_pos.x <= this->top_left_pos.x && another_room.top_left_pos.x+another_room.size.x >= this->top_left_pos.x))
        ||
        ((this->top_left_pos.y <= another_room.top_left_pos.y && this->top_left_pos.y+this->size.y >= another_room.top_left_pos.y)
        || (another_room.top_left_pos.y <= this->top_left_pos.y && another_room.top_left_pos.y+another_room.size.y >= this->top_left_pos.y)))

        return true;
    else
        return false;

}

void Room::Overlap_Fix(const Room &another_room){
    //very dummy way of making it not colide with each other
    //its moving randomly 15 tiles apart each room if it colides on some side
    //its 10 becouse size is max 10
    //its actually pty smart becouse it moves it the way it wont collide
    //but its dummy becouse it doesnt make it look smart
        sf::Vector2f change;
        while(this->Collision_Check(another_room)){
            if((this->top_left_pos.x <= another_room.top_left_pos.x && this->top_left_pos.x+this->size.x >= another_room.top_left_pos.x))
                change.x = -(std::rand()%15+2)*16.0*Globals::SCALE;
            if((another_room.top_left_pos.x <= this->top_left_pos.x && another_room.top_left_pos.x+another_room.size.x >= this->top_left_pos.x))
                change.x = (std::rand()%15+2)*16.0*Globals::SCALE;
            if((this->top_left_pos.y <= another_room.top_left_pos.y && this->top_left_pos.y+this->size.y >= another_room.top_left_pos.y))
                change.y = -(std::rand()%15+2)*16.0*Globals::SCALE;
            if((another_room.top_left_pos.y <= this->top_left_pos.y && another_room.top_left_pos.y+another_room.size.y >= this->top_left_pos.y))
                change.y = (std::rand()%15+2)*16.0*Globals::SCALE;



            this->top_left_pos += change;
        }

        //placing tiles in new places so they match top_left_pos and size of room
        for(auto & it: Tiles){
            it.Move(change);
        }
}

