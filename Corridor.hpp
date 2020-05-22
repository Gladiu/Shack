#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Tile.hpp>
#include <Room.hpp>
class Corridor : public sf::Drawable{
    public:
        void GiveTexture(sf::Texture *input_texture);
        void GenerateCorridor(sf::Vector2f departurepos,sf::Vector2f finalpos);
        void SetNextLevelTrigger(bool trigger);
        bool WillCollide(int direction, int lenght,const sf::Vector2f position);
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    private:
        std::vector<Tile> Tiles;
        sf::Texture* texture_ptr;
        bool next_level_trigger;
};

