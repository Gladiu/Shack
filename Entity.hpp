#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Entity : public sf::Drawable{
    public:
        Entity();
        virtual void Update(sf::Time time)=0;
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
        sf::Vector2f speed_vector;
        float rotation_speed;
        float max_rotation;
    private:

};



