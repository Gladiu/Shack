#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <utility>
#include "Entity.hpp"

Entity::Entity(){

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    target.draw(entity_sprite,states);
}
void Entity::Update(sf::Time time){}



