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
        sf::Vector2f GetPosition()const;
        sf::Vector2f GetSize();
        bool Overlap(const Tile &tile);
        bool GetEmpty();
        sf::FloatRect GetGlobalBounds();
        void setTextureRect(const sf::IntRect &rect);
        sf::Color getColor();
        void SetColor(sf::Color kolor);
        void SetRotation(int rotation);
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

    private:
        bool is_exit;
        sf::Sprite sprite;
        std::shared_ptr<sf::Texture> texture;
        sf::Vector2f position;

};
