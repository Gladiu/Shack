#include "Corridor.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include "Globals.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
void Corridor::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    for(auto it:Tiles)
        target.draw(it,states);
}
