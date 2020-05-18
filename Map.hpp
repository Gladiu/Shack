#pragma once
#include "Tile.hpp"
#include "Room.hpp"
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

        std::vector<Room> Rooms;
        sf::Texture floor_texture;
        sf::Texture wall_texture;
};


