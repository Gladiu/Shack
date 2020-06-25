#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Button.hpp"
class Menu : public sf::Drawable{
public:
    Menu();
    void Interact(sf::Vector2f mouse_pos,bool left_btn_click);
    const bool & GetContinueGame()const;
    const bool & GetExitGame() const;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
protected:
    bool continue_game;
    bool exit_game;
    sf::Music music;
    std::vector<sf::Sprite> sprites;
    sf::Texture play_button_txt;
    std::shared_ptr<sf::Texture> play_button_txt_ptr;
    sf::Texture exit_button_txt;
    std::shared_ptr<sf::Texture> exit_button_txt_ptr;
    sf::Sprite title;
    sf::Texture title_txt;
    Button playbutton;
    Button exitbutton;
    sf::Sound accept;
    sf::SoundBuffer accept_bfr;
};


