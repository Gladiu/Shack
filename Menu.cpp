#include "Menu.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

Menu::Menu(){
    continue_game = false;
    exit_game = false;
    title_txt.loadFromFile("textures/title.png");
    title.setTexture(title_txt);
    title.setScale(Globals::SCALE,Globals::SCALE);
    title.setOrigin(40,24);
    title.setPosition(0,-40*Globals::SCALE);

    this->play_button_txt.loadFromFile("textures/play_button.png");
    play_button_txt_ptr = std::make_shared<sf::Texture>(play_button_txt);

    this->exit_button_txt.loadFromFile("textures/quit_button.png");
    exit_button_txt_ptr = std::make_shared<sf::Texture>(exit_button_txt);


    playbutton.SetTexture(play_button_txt_ptr);
    playbutton.SetPosition(sf::Vector2f(10.0,0.0));
    exitbutton.SetTexture(exit_button_txt_ptr);
    exitbutton.SetPosition(sf::Vector2f(10.0,32.0*Globals::SCALE));
    accept_bfr.loadFromFile("sounds/applied.wav");
    accept.setBuffer(accept_bfr);
    accept.setVolume(35);
}

void Menu::Interact(sf::Vector2f mouse_pos,bool left_btn_click){
    if(playbutton.MouseOnButton(mouse_pos) && left_btn_click){
        continue_game = true;
        accept.play();
    }
    if(exitbutton.MouseOnButton(mouse_pos) && left_btn_click){
        exit_game = true;
        accept.play();
    }
}
void Menu::Update(sf::Time elapsed){

}
void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(playbutton,states);
        target.draw(exitbutton,states);
        target.draw(title,states);
}

bool Menu::GetContinueGame(){
    return continue_game;
}

bool Menu::GetExitGame(){
    return exit_game;
}
