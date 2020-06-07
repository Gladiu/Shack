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
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
        int ammount_of_rooms;
        std::vector<std::vector<Tile>> LevelTiles;
        std::vector<sf::Vector2f> Position_of_tiles;
        sf::Texture floor_texture;
        std::shared_ptr<sf::Texture> floor_texture_ptr;
        sf::Texture wall_texture;
        sf::Vector2f size,spawn_space_of_player;
};


