#pragma once
#include "Tile.hpp"
#include "Room.hpp"
#include "Corridor.hpp"
#include "Entity.hpp"
#include <memory>
#include <vector>

class Map : public sf::Drawable{
    public:
        Map();
        void Generate();
        sf::Vector2f Get_Spawn();
        void CheckIfFalling(Entity &smth);
        void CheckIfFalling(std::vector<Entity> &smth);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
        void UpdateRenderCenter(sf::Vector2f position);
        void SetRenderDistance(float distance);
        std::vector<sf::Vector2f> GetSpawningSpaces();
    protected:
        int ammount_of_rooms;
        std::vector<std::vector<Tile>> LevelTiles;
        std::vector<sf::Vector2f> TilePos;
        sf::Texture floor_texture;
        std::shared_ptr<sf::Texture> floor_texture_ptr;
        sf::Texture wall_texture;
        sf::Texture boom_texture;
        sf::Vector2f size,spawn_space_of_player,beginning_of_map;
        sf::Vector2f render_center;
        float render_distance;
};


