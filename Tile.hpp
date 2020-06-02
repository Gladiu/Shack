#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

class Tile : public sf::Drawable{
    public:
        Tile();
        Tile(const Tile &other);
        void Generate(std::shared_ptr<sf::Texture> input_texture);
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
        std::shared_ptr<sf::Texture> texture;

};
