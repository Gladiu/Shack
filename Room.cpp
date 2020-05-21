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



void Room::Generate(sf::Vector2f position,sf::Texture *input_texture,int where){


    //generating dimensions of room
    this->size.y  = 16.0 * Globals::SCALE*(std::rand()%2+4);
    this->size.x = 16.0 * Globals::SCALE*(std::rand()%2+4);
    top_left_pos = sf::Vector2f(0.0,0.0);

    //filling room with floor tiles
    bool generating=true;
    sf::Vector2f last_tile_pos;
    last_tile_pos.x=0.0;
    last_tile_pos.y=0.0;
    while(generating){
        Tile generated_tile;
        generated_tile.Generate(input_texture);
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
    //making so position and int where describe exact position of the room
    //if where 0 position should describe position of middle left tile
    //1 top 2 right 3 down, its all clockwise
    std::vector<sf::Vector2f> Relations_between_tiles;
    std::vector<sf::Vector2f> Positions_of_extreme_tiles;
    for(auto& it:Tiles){
        switch(where){
        case 0:
            if(it.GetPosition().y == top_left_pos.y)
                Positions_of_extreme_tiles.emplace_back(it.GetPosition());
            break;
        case 1:
            if(it.GetPosition().x == top_left_pos.x)
                Positions_of_extreme_tiles.emplace_back(it.GetPosition());
            break;
        case 2:
            if(it.GetPosition().y == top_left_pos.y+size.y)
                Positions_of_extreme_tiles.emplace_back(it.GetPosition());
            break;
        case 3:
            if(it.GetPosition().x == top_left_pos.x+size.x)
                Positions_of_extreme_tiles.emplace_back(it.GetPosition());
            break;
        }
    }
    for(auto it:Tiles){
        Relations_between_tiles.emplace_back(it.GetPosition()-Positions_of_extreme_tiles[Positions_of_extreme_tiles.size()/2]);
    }
    for(int i = 0; i < static_cast<int>(Tiles.size()); i++){
        Tiles[i].setPos(Relations_between_tiles[i].x+position.x,Relations_between_tiles[i].y+position.y);
    }
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
    if((((this->top_left_pos.x <= another_room.top_left_pos.x && this->top_left_pos.x+this->size.x >= another_room.top_left_pos.x)
        || (another_room.top_left_pos.x <= this->top_left_pos.x && another_room.top_left_pos.x+another_room.size.x >= this->top_left_pos.x))
        &&
        ((this->top_left_pos.y <= another_room.top_left_pos.y && this->top_left_pos.y+this->size.y >= another_room.top_left_pos.y)
        || (another_room.top_left_pos.y <= this->top_left_pos.y && another_room.top_left_pos.y+another_room.size.y >= this->top_left_pos.y)))
            ||
            (this->top_left_pos.x == another_room.top_left_pos.x || this->top_left_pos.x+this->size.x == another_room.top_left_pos.x
                ||another_room.top_left_pos.x == this->top_left_pos.x || another_room.top_left_pos.x+another_room.size.x == this->top_left_pos.x
                || this->top_left_pos.y == another_room.top_left_pos.y || this->top_left_pos.y+this->size.y == another_room.top_left_pos.y
                || another_room.top_left_pos.y == this->top_left_pos.y || another_room.top_left_pos.y+another_room.size.y == this->top_left_pos.y)
        )

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
        if((this->top_left_pos.x <= another_room.top_left_pos.x && this->top_left_pos.x+this->size.x >= another_room.top_left_pos.x)
            || this->top_left_pos.x == another_room.top_left_pos.x || this->top_left_pos.x+this->size.x == another_room.top_left_pos.x)
            change.x = -(std::rand()%15+2)*16.0*Globals::SCALE;
        if((another_room.top_left_pos.x <= this->top_left_pos.x && another_room.top_left_pos.x+another_room.size.x >= this->top_left_pos.x)
            || another_room.top_left_pos.x == this->top_left_pos.x || another_room.top_left_pos.x+another_room.size.x == this->top_left_pos.x)
            change.x = (std::rand()%15+2)*16.0*Globals::SCALE;
        if((this->top_left_pos.y <= another_room.top_left_pos.y && this->top_left_pos.y+this->size.y >= another_room.top_left_pos.y)
            || this->top_left_pos.y == another_room.top_left_pos.y || this->top_left_pos.y+this->size.y == another_room.top_left_pos.y)
            change.y = -(std::rand()%15+2)*16.0*Globals::SCALE;
        if((another_room.top_left_pos.y <= this->top_left_pos.y && another_room.top_left_pos.y+another_room.size.y >= this->top_left_pos.y)
           || another_room.top_left_pos.y == this->top_left_pos.y || another_room.top_left_pos.y+another_room.size.y == this->top_left_pos.y)
            change.y = (std::rand()%15+2)*16.0*Globals::SCALE;



        this->top_left_pos += change;
    }

    //placing tiles in new places so they match top_left_pos and size of room
    for(auto & it: Tiles){
        it.Move(change);
    }
}

bool Room::GetHasExit(){
    return this->has_exit;
}

void Room::Emplace_Back_Connected_Room_Number(int number){
    Connected_to_room.emplace_back(number);
}

sf::Vector2f Room::GetValidExit(sf::Vector2f position_of_exit){
    //you are passing an exit position!!
    //top left right down are bound to how sfml renderwindow sees coordinates
    bool down,top,left,right = false;//bool that says where is the current exit that we dont want to mess
    //finding in which direction to go
    for(auto it:Tiles){
        if(position_of_exit.x + Globals::SCALE*16 == it.GetPosition().x){
            down = true;
            break;
        }
        if(position_of_exit.x - Globals::SCALE*16 == it.GetPosition().x){
            top = true;
            break;
        }
        if(position_of_exit.y + Globals::SCALE*16 == it.GetPosition().y){
           left = true;
           break;
       }
        if(position_of_exit.y - Globals::SCALE*16 == it.GetPosition().y){
            right = true;
            break;
        }
    }
    bool finding = true;
    bool nextleft,nextright,nexttop,nextdown;
    while(finding){
        int next_exit_pos = std::rand()%4;
        switch(next_exit_pos){
        case 0:
            nextleft = true;
            break;
        case 1:
            nexttop = true;
            break;
        case 2:
            nextright = true;
            break;
        case 3:
            nextdown = true;
            break;
        }
        if(!((nextleft && left) || (nextright && right) || (nexttop && top) || (nextdown && down)))
            finding = false;
    }
    finding = true;
    //finding middle tile
    sf::Vector2f buffer = Tiles[Tiles.size()/2].GetPosition();
    //generating next exit
    while(finding){
        finding = false;
        for(auto it:Tiles){
            if(nexttop && (buffer.x-Globals::SCALE*16 == it.GetPosition().x)){
                buffer = it.GetPosition();
                finding = true;
            }
            if(nextdown && (buffer.x+Globals::SCALE*16 == it.GetPosition().x)){
                buffer = it.GetPosition();
                finding = true;
            }
            if(nextright && (buffer.y-Globals::SCALE*16 == it.GetPosition().y)){
                buffer = it.GetPosition();
                finding = true;
            }
            if(nextleft && (buffer.y+Globals::SCALE*16==it.GetPosition().y)){
                buffer = it.GetPosition();
                finding = true;
            }
        }
    }
    return buffer;
}

void Room::AddExit(sf::Vector2f exit){
    ExitPos.emplace_back(exit);
}

sf::Vector2f Room::GetExitPoint(){
    return ExitPos[ExitPos.size()-1];
}

sf::Vector2f Room::GenerateLeftExit(){
    sf::Vector2f buffer;
    buffer.x = top_left_pos.x+(size.x/2);
    buffer.y = top_left_pos.y;
    this->ExitPos.emplace_back(buffer);
    return buffer;
}
