#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Tile.hpp>
class Corridor : public sf::Drawable{

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    private:
        std::vector<Tile> Tiles;
};

