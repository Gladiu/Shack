#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Boom.hpp"
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
        std::vector<Entity> boomers;
    protected:
        sf::Texture boom_texture;
        std::shared_ptr<sf::Texture> boom_texture_ptr;

};
