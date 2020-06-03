#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Tile.hpp"
#include "Room.hpp"
#include "Corridor.hpp"
#include "Globals.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

Map::Map(){
    std::cout<<"Loading Map assets..."<<std::endl;
    this->floor_texture.loadFromFile("textures/floor.png");
    this->floor_texture.setRepeated(true);
    floor_texture_ptr = std::make_shared<sf::Texture>(floor_texture);
    ammount_of_rooms = 55; //bigger == longer generating time lololololol
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    for(auto it:Rooms)
        target.draw(it,states);
    for(auto it:Corridors)
        target.draw(it,states);
}

void Map::Generate(){
    //generating rooms
    //basically its generating rooms, then corridor from it then next room etc

    sf::Vector2f start,end,position,place_room_here;
    place_room_here = sf::Vector2f(0.0,0.0);
    int position_of_corridor = 0;
    for(int i = 0; i<ammount_of_rooms; i++){

        Room room;

        if(i>0){
            Corridor corridor;
            corridor.GiveTexture(floor_texture_ptr);
            start = Rooms[i-1].GetValidExit(end);

            int direction_of_next_corridor = Rooms[i-1].GetDirectionOfExit();            
            int lenght = (std::rand()%10+6)*Globals::SCALE*16;
            std::cout<<i<<std::endl;
/*            bool colliding = true;
            while(colliding){
                colliding = false;
                for(auto it : Rooms){
                    //colliding = it.WillCollide(direction_of_next_corridor,lenght,start);
                    if(colliding)
                        break;

                }
                for(auto it : Corridors){
                    //colliding = it.WillCollide(direction_of_next_corridor,lenght,start);
                    if(colliding)
                        break;
                }
                if(colliding){
                    start = Rooms[i-1].GetValidExit(start);
                    direction_of_next_corridor = Rooms[i-1].GetDirectionOfExit();
                    lenght = (std::rand()%10+4)*Globals::SCALE*16;
                }

            }*/
            //1 top 2 right 3 down, its all clockwise
            //direction corridor., at the end of it we will generate a room
            Rooms[i-1].AddExit(start);
            bool generating = true;
            while(generating){
                std::cout<<direction_of_next_corridor;
                switch(direction_of_next_corridor){
                    case 0:
                        end.y -= Globals::SCALE*16;
                        if(end.y == start.y - lenght){
                            place_room_here.y = start.y + lenght;
                            place_room_here.x = start.x;
                            generating = false;
                        }
                        break;
                    case 1:
                        end.x -= Globals::SCALE*16;
                        if(end.x == start.x - lenght){
                            place_room_here.x = start.x + lenght;
                            place_room_here.y = start.y;
                            generating = false;
                        }
                        break;
                    case 2:
                        end.y += Globals::SCALE*16;
                        if(end.y == start.y + lenght){
                            place_room_here.y = start.y + lenght;
                            place_room_here.x = start.x;
                            generating = false;
                            std::cout<<"B";
                        }
                        break;
                    case 3:
                        end.x += Globals::SCALE*16;
                        if(end.x == start.x + lenght){
                            place_room_here.x = start.x + lenght;
                            place_room_here.y = start.y;
                            generating = false;
                        }
                        break;
                }
            }
            corridor.GenerateCorridor(start,end);

            this->Corridors.emplace_back(corridor);
            room.AddExit(end);

        }

        room.Generate(end,floor_texture_ptr,position_of_corridor);

        if(i==0){
            room.GenerateLeftExit();
        }
        this->Rooms.push_back(room);
    }
    //add function to add all tiles into Position_of_tiles vector
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
