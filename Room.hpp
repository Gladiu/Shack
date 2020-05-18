#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include <vector>
class Room : public sf::Drawable{
    public:
        Room();
        void Generate(sf::Texture *input_texture);
        sf::Vector2f Get_Top_Left_Corner();
        void Overlap_Fix(const Room &another_room);
        bool Collision_Check(Room another_room);

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    private:
        std::vector<Tile> Tiles;
        sf::Vector2f top_left_pos;
        sf::Vector2f size;

};
