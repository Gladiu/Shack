#pragma once
#include "Tile.hpp"
#include "Room.hpp"
#include "Corridor.hpp"
#include <memory>
#include <vector>

class Map : public sf::Drawable{
    public:
        Map();
        void Generate();
        sf::Vector2f Get_Spawn();
        std::vector<sf::Vector2f> Generate_Path(sf::Vector2f position);
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
        int ammount_of_rooms;
        std::vector<Room> Rooms;
        std::vector<Corridor> Corridors;
        std::vector<sf::Vector2f> Position_of_tiles;
        sf::Texture floor_texture;
        std::shared_ptr<sf::Texture> floor_texture_ptr;
        sf::Texture wall_texture;
};


