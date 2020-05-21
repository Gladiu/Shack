#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Tile.hpp"
#include "Corridor.hpp"
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
    int ammount_of_rooms = 2;
    bool repeat_alghoritm = true;
    sf::Vector2f newexit,oldexit,position;
    position = sf::Vector2f(0.0,0.0);
    int position_of_corridor = 0;
    for(int i = 0; i<=ammount_of_rooms; i++){
        Room room;
        Corridor corridor;
        if(i>0){

            
            corridor.GenerateCorridor(Rooms[i-1].GetExitPoint(),newposition);
          //  room.AddExit(last_exit);
            this->Corridors.emplace_back(corridor);
        }
        room.Generate(newexit,&floor_texture,position_of_corridor);
        if(i==0)
            oldexit = room.GenerateLeftExit();
        this->Rooms.push_back(room);
    }


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
