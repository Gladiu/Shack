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

Room::Room(const Room& other){
    this->top_left_pos = other.top_left_pos;
    this->size = other.size;
    this->Tiles = other.Tiles;
    this->ExitPos = other.ExitPos;
    this->Connected_to_room = other.Connected_to_room;
    this->has_exit = other.has_exit;
}


void Room::Generate(sf::Vector2f position,std::shared_ptr<sf::Texture> input_texture,int where){


    //generating dimensions of room
    this->size.y  = 16.0 * Globals::SCALE*(std::rand()%8+2);
    this->size.x = 16.0 * Globals::SCALE*(std::rand()%8+2);
    top_left_pos = sf::Vector2f(0.0,0.0);

    //filling room with floor tiles
    bool generating=true;
    sf::Vector2f last_tile_pos;
    last_tile_pos.x=0.0;
    last_tile_pos.y=0.0;
    while(generating){
        Tile generated_tile;
        generated_tile.Generate(input_texture);
        generated_tile.setPos(last_tile_pos.x,last_tile_pos.y);

        if(last_tile_pos.y < this->size.y)
            last_tile_pos.y += 16.0*Globals::SCALE;
        else{
            if(last_tile_pos.y >= this->size.y){
                last_tile_pos.y = 0;
                last_tile_pos.x += 16.0*Globals::SCALE;
            }
            if(last_tile_pos.x > this->size.x){
                generating = false;
            }
        }
        Tiles.push_back(generated_tile);
    }
    //making so position and int where describe exact position of the room
    //here its flipped so 2 = left 1  =down 0 = top
    std::vector<sf::Vector2f> Relations_between_tiles;
    std::vector<sf::Vector2f> Positions_of_extreme_tiles;
    for(auto& it:Tiles){
        switch(where){
            case 2:
                if(it.GetPosition().y == top_left_pos.y)
                    Positions_of_extreme_tiles.emplace_back(it.GetPosition());
                break;
            case 3:
                if(it.GetPosition().x == top_left_pos.x)
                    Positions_of_extreme_tiles.emplace_back(it.GetPosition());
                break;
            case 0:
                if(it.GetPosition().y == top_left_pos.y+size.y)
                    Positions_of_extreme_tiles.emplace_back(it.GetPosition());
                break;
            case 1:
                if(it.GetPosition().x == top_left_pos.x+size.x)
                    Positions_of_extreme_tiles.emplace_back(it.GetPosition());
                break;
        }
    }
    sf::Vector2f origin = Positions_of_extreme_tiles[Positions_of_extreme_tiles.size()/2];
    for(auto it:Tiles){
        Relations_between_tiles.emplace_back(it.GetPosition()-origin);
    }
    for(int i = 0; i <= static_cast<int>(Tiles.size()); i++){
        Tiles[i].setPos(Relations_between_tiles[i].x+position.x,Relations_between_tiles[i].y+position.y);
    }
    top_left_pos = Tiles[0].GetPosition();
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
    //you are passing an enternance position!!
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
            nextright = false;
            nexttop = false;
            nextdown = false;
            break;
        case 1:
            nexttop = true;
            nextdown = false;
            nextleft = false;
            nextright = false;
            break;
        case 2:
            nextright = true;
            nexttop = false;
            nextdown = false;
            nextleft = false;
            break;
        case 3:
            nextdown = true;
            nextleft = false;
            nextright = false;
            nexttop = false;
            break;
        }
        if(!((nextleft && left) || (nextright && right) || (nexttop && top) || (nextdown && down))){
            finding = false;
        }
    }
    finding = true;
    //finding middle tile
    sf::Vector2f buffer = Tiles[Tiles.size()/2].GetPosition();
    //generating next exit
    while(finding){
        finding = false;
        for(auto it:Tiles){
            if(nexttop && (buffer.x-Globals::SCALE*16 == it.GetPosition().x)){
                buffer.x -= Globals::SCALE*16;
                finding = true;

            }
            if(nextdown && (buffer.x+Globals::SCALE*16 == it.GetPosition().x)){
                buffer.x += Globals::SCALE*16;
                finding = true;

            }
            if(nextright && (buffer.y-Globals::SCALE*16 == it.GetPosition().y)){
                buffer.y -= Globals::SCALE*16;
                finding = true;

            }
            if(nextleft && (buffer.y+Globals::SCALE*16==it.GetPosition().y)){
                buffer.y += Globals::SCALE*16;
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
int Room::GetDirectionOfExit(){
    //copy pasta of code from previous function lolololololol
    sf::Vector2f position_of_exit = this->GetExitPoint();
    int buffer;
    for(auto it:Tiles){
        if(position_of_exit.x + Globals::SCALE*16 == it.GetPosition().x){
            buffer = 3;
            break;
        }
        if(position_of_exit.x - Globals::SCALE*16 == it.GetPosition().x){
            buffer = 1;
            break;
        }
        if(position_of_exit.y + Globals::SCALE*16 == it.GetPosition().y){
           buffer = 0;
           break;
       }
        if(position_of_exit.y - Globals::SCALE*16 == it.GetPosition().y){
            buffer = 2;
            break;
        }
    }
return buffer;
}

bool Room::WillCollide(int direction, int lenght,const sf::Vector2f position){
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

void Room::ReplaceExit(sf::Vector2f newexit){
    this->ExitPos[1] = newexit;
}
