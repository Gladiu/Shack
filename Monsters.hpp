#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.hpp"
#include "Boom.hpp"
#include "Robot.hpp"
#include "Player.hpp"
#include <memory>

class Monsters : public  sf::Drawable{
    public:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        Monsters();
        void Update(sf::Time time,sf::Vector2f render_center, float render_distance);
        void Generate(const std::vector<sf::Vector2f> & legal_positions);
        bool AreClicked(sf::Vector2f position);
        void Interact(Player &player);
        std::vector<Entity> members;
    protected:
        sf::Texture boom_texture;
        std::shared_ptr<sf::Texture> boom_texture_ptr;
        sf::Texture robot_texture;
        std::shared_ptr<sf::Texture> robot_texture_ptr;
        sf::SoundBuffer robot_hit_bfr;
        sf::Sound robot_hit;
        sf::SoundBuffer boom_hit_bfr;
        sf::Sound boom_hit;
        sf::Clock robot_hit_sound_cooldown;
        sf::SoundBuffer boom_death_snd_bfr;
        sf::SoundBuffer robot_death_snd_bfr;
        sf::Sound boom_death;
        sf::Sound robot_death;



};
