#include "Button.hpp"

Button::Button(){
    click_bfr.loadFromFile("sounds/select.wav");
    click.setBuffer(click_bfr);
    sprite.setScale(Globals::SCALE,Globals::SCALE);
    sprite.setOrigin(32.0,0.0);

}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(sprite,states);
}

void Button::SetTexture(std::shared_ptr<sf::Texture> texture_ptr){
    my_texture_ptr = texture_ptr;
    sprite.setTexture(*my_texture_ptr);
    sprite.setTextureRect(sf::IntRect(0.0,0.0,64.0,16.0));
}

bool Button::MouseOnButton(sf::Vector2f mouse_pos){
    if(sprite.getGlobalBounds().contains(mouse_pos)){
        sprite.setTextureRect(sf::IntRect(0.0,16.0,64.0,16.0));
        return true;
    }
    else{
        sprite.setTextureRect(sf::IntRect(0.0,0.0,64.0,16.0));
        click.play();
        return false;
    }
    return false;
}

void Button::SetPosition(sf::Vector2f newpos){
    sprite.setPosition(newpos);
}
