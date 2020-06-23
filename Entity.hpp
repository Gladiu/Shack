#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
class Entity : public sf::Drawable{
    public:
        Entity();
        void Update(sf::Time time);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
        sf::FloatRect GetGlobalBounds();
        void SetPath(const sf::Vector2f &position);
        sf::Vector2f GetPosition();
        void IsFalling(bool outsidemap);
        bool IsFalling();
        sf::Vector2f GetScale();
        void Bump(sf::Vector2f position_of_bump);\
        void ResetPath();
        bool GetMovable();
        void Animate();
    protected:
        struct Value{
            int current;
            int max;
        };
        Value health,mana;
        std::shared_ptr<sf::Texture> entity_texture;
        sf::Sprite entity_sprite;
        float speed;
        sf::Vector2f speed_vector;
        float rotation_speed;
        float max_rotation;
        bool in_desired_position;
        bool first_move_check;
        bool falling;
        bool monster;
        bool movable;
        bool progress_animation;
        float push_factor;
        sf::Clock idle_anim;
        sf::Vector2f desired_position;
        sf::Vector2f temp;
        sf::Vector2f temp_inert;
        sf::Vector2f path;
        sf::Vector2f inertial_force;
        sf::Texture texture;
        sf::SoundBuffer snd_bfr;
        sf::Sound snd;
};



