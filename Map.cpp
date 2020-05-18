#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Tile.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <vector>

Map::Map(){
    std::cout<<"Loading Map assets..."<<std::endl;
    this->floor_texture.loadFromFile("textures/floor.png");
    this->floor_texture.setRepeated(true);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    for(auto it:Rooms)
        target.draw(it,states);
}

void Map::Generate(){
    //generating rooms
    int ammount_of_rooms = 8;
    for(int i =0;i<ammount_of_rooms;i++){
        Room room;
        room.Generate(&floor_texture);
        if(i>0){
            //basically fixing overlaping rooms for new room created
            bool repeat_alghoritm = true;
            while(repeat_alghoritm){
                repeat_alghoritm = false;
                for(auto it:Rooms){
                    if(room.Collision_Check(it)){
                        std::cout<<"passed the if in map.cpp"<<std::endl;
                        room.Overlap_Fix(it);
                        repeat_alghoritm = true;
                    }
                }
            }
        }
        this->Rooms.push_back(room);
    }
    //generating coridors
}

sf::Vector2f Map::Get_Spawn(){
    sf::Vector2f buffor;
    buffor.x = Rooms[0].Get_Top_Left_Corner().x+8*5;
    buffor.y = Rooms[0].Get_Top_Left_Corner().y+8*5;
    return buffor;
}

std::vector<sf::Vector2f> Map::Generate_Path(sf::Vector2f position){
    std::vector<sf::Vector2f> buffer;

    if(true)//check if mouse position is in the same room like from position
    return buffer;
}
