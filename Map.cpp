#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Tile.hpp"
#include "Room.hpp"
#include "Corridor.hpp"
#include "Globals.hpp"
#include "Boom.hpp"
#include <math.h>
#include <vector>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <fstream>
#include <string>

Map::Map(){
    std::cout<<"Loading Map assets..."<<std::endl;
    this->floor_texture.loadFromFile("textures/floor.png");
    this->floor_texture.setRepeated(true);
    floor_texture_ptr = std::make_shared<sf::Texture>(floor_texture);
    ammount_of_rooms = 200; //bigger means less fps
    debug =3;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    for(auto &it: TilePos){
            if(Globals::DISTANCE(LevelTiles[it.x][it.y].GetPosition(),render_center)<render_distance)
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
                LevelTiles[x][y].setTextureRect(sf::IntRect(0,16*(std::rand()%debug),16,16));
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
                LevelTiles[x][y].setTextureRect(sf::IntRect(0,16*(std::rand()%debug),16,16));
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

this->Beutify();


}

void Map::Beutify(){
    int debug = 3;
    for(auto &it:TilePos){
        std::vector<bool> filled;
        for(int j = -1;j <2; j++){
            for(int i = -1;i <2; i++){
                if(i+it.x >=0 && i+it.x <LevelTiles.size() && j+it.y >=0 && j+it.y <LevelTiles[0].size()){
                    filled.emplace_back(LevelTiles[i+it.x][j+it.y].GetEmpty());
                }
                else
                    filled.emplace_back(true);
            }
        }
        //pionowy tunel
        if(!filled[1] && filled[3] && filled[5] && !filled[7])
            LevelTiles[it.x][it.y].setTextureRect(sf::IntRect(32,16*(std::rand()%debug),16,16));
        //poziomy tunel
        if(filled[1] && !filled[3] && !filled[5] && filled[7]){
            LevelTiles[it.x][it.y].setTextureRect(sf::IntRect(32,16*(std::rand()%debug),16,16));
            LevelTiles[it.x][it.y].SetRotation(90);
        }

        //szczota na lewo
        if(!filled[1]  && filled[3] && !filled[5] && !filled[7] ){
            LevelTiles[it.x][it.y].setTextureRect(sf::IntRect(48,16*(std::rand()%debug),16,16));
            LevelTiles[it.x][it.y].SetRotation(180);
        }
        //szczota na prawo
        if(!filled[1] && !filled[3] && filled[5] && !filled[7])
            LevelTiles[it.x][it.y].setTextureRect(sf::IntRect(48,16*(std::rand()%debug),16,16));
        //szczota u góry
        if( filled[1] && !filled[3] && !filled[5] && !filled[7]){
            LevelTiles[it.x][it.y].setTextureRect(sf::IntRect(48,16*(std::rand()%debug),16,16));
            LevelTiles[it.x][it.y].SetRotation(-90);
        }

        //szczora na dole
        if(!filled[1]  && !filled[3] && !filled[5] && filled[7] ){
            LevelTiles[it.x][it.y].setTextureRect(sf::IntRect(48,16*(std::rand()%debug),16,16));
            LevelTiles[it.x][it.y].SetRotation(90);
        }

        //prawy dolny róg
        if(!filled[1] &&  !filled[3] && filled[5]  && filled[7]){
            LevelTiles[it.x][it.y].setTextureRect(sf::IntRect(16,16*(std::rand()%debug),16,16));
            LevelTiles[it.x][it.y].SetRotation(90);
        }
        //lewy dolny róg
        if(!filled[1] &&  filled[3] && !filled[5]  && filled[7]){
            LevelTiles[it.x][it.y].setTextureRect(sf::IntRect(16,16*(std::rand()%debug),16,16));
            LevelTiles[it.x][it.y].SetRotation(180);
        }
        //prawy górny róg
        if(filled[1] &&  !filled[3] && filled[5]  && !filled[7]){
            LevelTiles[it.x][it.y].setTextureRect(sf::IntRect(16,16*(std::rand()%debug),16,16));
        }
        //lewy górny róg
        if(filled[1] &&  filled[3] && !filled[5]  && !filled[7]){
            LevelTiles[it.x][it.y].setTextureRect(sf::IntRect(16,16*(std::rand()%debug),16,16));
            LevelTiles[it.x][it.y].SetRotation(-90);
        }

        //if(filled[0] && filled[1] && filled[2] && filled[3] && filled[4] && filled[5] && filled[6] && filled[7] && filled[8]) */
    }
}

sf::Vector2f Map::Get_Spawn(){
    return LevelTiles[TilePos[0].x][TilePos[0].y].GetPosition();
}
void Map::CheckIfFalling(Entity &smth){
    sf::FloatRect rect = smth.GetGlobalBounds();
    rect.width /=1.5;
    rect.height /=1.5;
    bool outsidemap = true;
    for(auto &it:TilePos){
            if(Globals::DISTANCE(LevelTiles[it.x][it.y].GetPosition(),render_center) < render_distance && LevelTiles[it.x][it.y].GetGlobalBounds().intersects(rect)){
                outsidemap = false;
                break;
            }
    }
    smth.IsFalling(outsidemap);

}
void Map::CheckIfFalling(std::vector<Entity> &smth){
    for(auto &it:smth){
        if(Globals::DISTANCE(it.GetPosition(),render_center)<render_distance)
            CheckIfFalling(it);
    }

}


void Map::UpdateRenderCenter(sf::Vector2f position){
    render_center = position;
}

void Map::SetRenderDistance(float distance){
    render_distance = distance;
}

std::vector<sf::Vector2f> Map::GetSpawningSpaces(){
    std::vector<sf::Vector2f> anwser;
    for(auto &it:TilePos){
        //if(Globals::DISTANCE(LevelTiles[it.x][it.y].GetPosition(),render_center)>render_distance)
            anwser.emplace_back(LevelTiles[it.x][it.y].GetPosition());
    }
    return anwser;
}

void Map::GenerateFromFile(std::string path){
    beginning_of_map = sf::Vector2f(0.0,0.0);
    std::string line;
    {
        std::fstream file(path,std::ios::in);

        Tile temp;
        std::vector<Tile> yplace;

        while (std::getline(file, line)) {
            yplace.emplace_back(temp);
        }

        for(auto it:line){
            LevelTiles.emplace_back(yplace);
        }


    }
    line.clear();
    int x=0;
    int y=0;
    std::fstream file(path,std::ios::in);
    while (std::getline(file, line)) {

        for(auto it:line){
            //std::cout<<it<std::endl;
            if(it=='X'){
                LevelTiles[x][y].Generate(floor_texture_ptr);
                LevelTiles[x][y].setTextureRect(sf::IntRect(0,16*(std::rand()%debug),16,16));
                LevelTiles[x][y].setPos(x*16*Globals::SCALE,y*16*Globals::SCALE);
            }
            else{
                //LevelTiles[x][y].
            }
            x++;
        }
        x=0;
        y++;
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

    file.close();
    //this->Beutify();
}
