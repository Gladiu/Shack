#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable{
    public:
        Tile();
        Tile(const Tile &other);
        void Generate(sf::Texture *input_texture);
        void setPos(float x,float y);
        void Move(const sf::Vector2f &offset);
        sf::Vector2f GetPosition();
        sf::Vector2f GetSize();
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

    private:
        bool transparent;
        bool collide;
        bool is_exit;
        sf::Sprite sprite;
        sf::Texture *texture;

};
