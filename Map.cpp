#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Tile.hpp"
#include "Room.hpp"
#include "Corridor.hpp"
#include "Globals.hpp"
#include <math.h>
#include <vector>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>

Map::Map(){
    std::cout<<"Loading Map assets..."<<std::endl;
    this->floor_texture.loadFromFile("textures/floor.png");
    this->floor_texture.setRepeated(true);
    floor_texture_ptr = std::make_shared<sf::Texture>(floor_texture);
    ammount_of_rooms = 200; //bigger means less fps
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    for(auto &it: TilePos){
            target.draw(LevelTiles[it.x][it.y],states);
    }
}

void Map::Generate(){
    //generating rooms
    //basically its generating rooms, then corridor from it then next room etc
    std::vector<Room> Rooms;
    std::vector<Corridor> Corridors;

    sf::Vector2f start,end,position,place_room_here;
    place_room_here = sf::Vector2f(0.0,0.0);
    int position_of_corridor = 0;
    for(int i = 0; i<ammount_of_rooms; i++){

        Room room;

        if(i>0){

            Corridor corridor;
            corridor.GiveTexture(floor_texture_ptr);
            start = Rooms[i-1].GetValidExit(end);

            int direction_of_next_corridor = std::rand()%4;// Rooms[i-1].GetDirectionOfExit();
            int lenght = (std::rand()%10+1)*Globals::SCALE*16;
            Rooms[i-1].AddExit(start);
            bool generating = true;
            while(generating){
                switch(direction_of_next_corridor){
                    case 0:
                        end.y -= Globals::SCALE*16;
                        if(end.y <= start.y - lenght){
                            place_room_here.y = start.y + lenght;
                            place_room_here.x = start.x;
                            generating = false;
                        }
                        break;
                    case 1:
                        end.x -= Globals::SCALE*16;
                        if(end.x <= start.x - lenght){
                            place_room_here.x = start.x + lenght;
                            place_room_here.y = start.y;
                            generating = false;
                        }
                        break;
                    case 2:
                        end.y += Globals::SCALE*16;
                        if(end.y >= start.y + lenght){
                            place_room_here.y = start.y + lenght;
                            place_room_here.x = start.x;
                            generating = false;
                        }
                        break;
                    case 3:
                        end.x += Globals::SCALE*16;
                        if(end.x >= start.x + lenght){
                            place_room_here.x = start.x + lenght;
                            place_room_here.y = start.y;
                            generating = false;
                        }
                        break;
                }
            }
            corridor.GenerateCorridor(start,end);

            Corridors.emplace_back(corridor);
            room.AddExit(end);

        }

        room.Generate(end,floor_texture_ptr,position_of_corridor);

        if(i==0){
            room.GenerateLeftExit();
        }
        Rooms.push_back(room);
    }
    //add function to add all tiles into one vector
    sf::Vector2f end_of_map = sf::Vector2f(0.0,0.0);
    beginning_of_map = sf::Vector2f(0.0,0.0);
    for(auto &it: Rooms){
        for(auto &at:it.GetTiles()){
            if( beginning_of_map.x > at.GetPosition().x )
                beginning_of_map.x = at.GetPosition().x;
            if (beginning_of_map.y > at.GetPosition().y )
                beginning_of_map.y = at.GetPosition().y;
            if( end_of_map.x < at.GetPosition().x )
                end_of_map.x = at.GetPosition().x;
            if (end_of_map.y < at.GetPosition().y )
                end_of_map.y = at.GetPosition().y;
        }
    }
    for(auto &it: Corridors){
        for(auto &at:it.GetTiles()){
            if( beginning_of_map.x > at.GetPosition().x )
                beginning_of_map.x = at.GetPosition().x;
            if (beginning_of_map.y > at.GetPosition().y )
                beginning_of_map.y = at.GetPosition().y;
            if( end_of_map.x < at.GetPosition().x )
                end_of_map.x = at.GetPosition().x;
            if (end_of_map.y < at.GetPosition().y )
                end_of_map.y = at.GetPosition().y;
        }
    }
    size.x = (end_of_map.x-beginning_of_map.x)/(Globals::SCALE*16);
    size.y = (end_of_map.y-beginning_of_map.y)/(Globals::SCALE*16);
    int x,y = 0;
    Tile temp;
    {
        std::vector<Tile> yplace;
        for(int j = 0; j <= size.y; j++){
            yplace.emplace_back(temp);
        }
        for(int i = 0; i <=  size.x; i++){
            LevelTiles.emplace_back(yplace);
        }
    }
    spawn_space_of_player = Rooms[0].GetTiles()[0].GetPosition();
    for(auto &it: Rooms){
        std::vector room_tiles = it.GetTiles();
        for(auto &at:room_tiles){
            x = ((at.GetPosition().x-beginning_of_map.x)/(16*Globals::SCALE));
            y = ((at.GetPosition().y-beginning_of_map.y)/(16*Globals::SCALE));
            if(LevelTiles[x][y].GetEmpty()){
                LevelTiles[x][y].Generate(floor_texture_ptr);
                LevelTiles[x][y].setTextureRect(sf::IntRect(std::rand()%4*16,0,16,16));
                LevelTiles[x][y].setPos(at.GetPosition().x,at.GetPosition().y);
            }
        }
    }
    for(auto &it: Corridors){
        std::vector room_tiles = it.GetTiles();
        for(auto &at:room_tiles){
            x = ((at.GetPosition().x-beginning_of_map.x)/(16*Globals::SCALE));
            y = ((at.GetPosition().y-beginning_of_map.y)/(16*Globals::SCALE));
            if(LevelTiles[x][y].GetEmpty()){
                LevelTiles[x][y].Generate(floor_texture_ptr);
                LevelTiles[x][y].setTextureRect(sf::IntRect(std::rand()%4*16,0,16,16));
                LevelTiles[x][y].setPos(at.GetPosition().x,at.GetPosition().y);
            }
        }
    }
    int i =0;
    int j =0;
    for(auto &it:LevelTiles ){

        for(auto &at:it){
            if(!at.GetEmpty())
                TilePos.emplace_back(sf::Vector2f(i,j));
            j++;
        }
        j=0;
        i++;
    }


}

sf::Vector2f Map::Get_Spawn(){
    return spawn_space_of_player;
}
bool Map::IsEmpty(const sf::FloatRect & rect){
    bool anwser = true;
    for(auto &it:TilePos){
            if(LevelTiles[it.x][it.y].GetGlobalBounds().intersects(rect))
                anwser = false;
    }
    return anwser;
}



