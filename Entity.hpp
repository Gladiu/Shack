#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Entity : public sf::Drawable{
    public:
        Entity();
    protected:
        struct Value{
            int current;
            int max;
        };


        Value health,mana;
        sf::Texture entity_texture;
        sf::Sprite entity_sprite;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
        float speed;
        float rotation_speed;
        float max_rotation;
    private:

};



