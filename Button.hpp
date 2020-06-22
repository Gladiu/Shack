#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <Globals.hpp>

class Button: public sf::Drawable{
public:
    Button();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void SetTexture(std::shared_ptr<sf::Texture> texture_ptr);
    bool MouseOnButton(sf::Vector2f mouse_pos);
    void SetPosition(sf::Vector2f newpos);
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    std::shared_ptr<sf::Texture> my_texture_ptr;
    sf::Sound click;
    sf::SoundBuffer click_bfr;
};


