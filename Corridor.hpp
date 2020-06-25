#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Tile.hpp>

class Corridor : public sf::Drawable{
    public:
        void GiveTexture(std::shared_ptr<sf::Texture> input_texture);
        void GenerateCorridor(sf::Vector2f departurepos,sf::Vector2f finalpos);
        void SetNextLevelTrigger(bool trigger);
        bool WillCollide(int direction, int lenght,const sf::Vector2f position);
        const sf::Vector2f Get_Top_Left_Corner()const;
        const std::vector<Tile> & GetTiles()const;
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    private:
        std::vector<Tile> Tiles;
        std::shared_ptr<sf::Texture> texture_ptr;
        bool next_level_trigger;
};

