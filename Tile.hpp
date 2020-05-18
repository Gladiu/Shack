#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable{
    public:
        Tile();
        void Generate(int intput,sf::Texture *input_texture);
        void setPos(float x,float y);
        void Move(const sf::Vector2f &offset);
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

    private:
        bool transparent;
        bool collide;
        sf::Sprite sprite;
        sf::Texture *texture;
        enum Tile_Type {floor};
        Tile_Type type;
};
