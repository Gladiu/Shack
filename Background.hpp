#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include <vector>
class Background : public sf::Drawable{
    public:
        Background();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
        void Proces(sf::Time time);
    protected:
        std::vector<Tile> bck_tiles;
        std::vector<Tile> background_for_tiles;
        std::vector<std::pair<int,bool>> glowing_tiles; //this bool is defining if we are darkening a tile
        sf::Texture texture;
        sf::Vector2f size;
};

