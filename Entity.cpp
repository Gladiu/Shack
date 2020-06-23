#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <utility>
#include "Entity.hpp"
#include "Globals.hpp"
#include <iostream>

Entity::Entity(){
    falling =false;
    in_desired_position = true;
    inertial_force = sf::Vector2f(0.0,0.0);
    idle_anim.restart();
    progress_animation = true;
    snd_bfr.loadFromFile("sounds/step.wav");
    snd.setBuffer(snd_bfr);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    target.draw(entity_sprite,states);
}


sf::FloatRect Entity::GetGlobalBounds(){
    return entity_sprite.getGlobalBounds();
}

void Entity::SetPath(const sf::Vector2f &position){
    path = position;
    in_desired_position = false;
    first_move_check = true;
    float temp = Globals::DISTANCE(position,entity_sprite.getPosition());
    speed_vector.x = ((position.x-entity_sprite.getPosition().x)/temp)*speed;
    speed_vector.y = ((position.y-entity_sprite.getPosition().y)/temp)*speed;
}

sf::Vector2f Entity::GetPosition(){
    return  entity_sprite.getPosition();
}

void Entity::IsFalling(bool outsidemap){
    falling = outsidemap;
}
bool Entity::IsFalling(){
    return falling;
}

void Entity::Update(sf::Time time){
    sf::Vector2f movement;


    if(!in_desired_position && !falling){

        //moving sprite
        movement = speed_vector*time.asSeconds();

        //teleport,shaking fix


        //walking animation
        if(entity_sprite.getRotation()+time.asSeconds()*rotation_speed > (max_rotation)
                && entity_sprite.getRotation()+time.asSeconds()*rotation_speed <(360-max_rotation)){
            rotation_speed = -rotation_speed;
            snd.play();

        }
        //moving eyes in direction of walking
        if(monster){
            if(movement.x>=0)
                entity_sprite.setScale(-std::abs(entity_sprite.getScale().x),entity_sprite.getScale().y);
            else
                entity_sprite.setScale(std::abs(entity_sprite.getScale().x),entity_sprite.getScale().y);

        }
        else{
            if(movement.x>=0)
                entity_sprite.setTextureRect(sf::IntRect(0,16,16,16));
            else
                entity_sprite.setTextureRect(sf::IntRect(0,0,16,16));
        }

        //moving and rotating sprite;
        entity_sprite.rotate(time.asSeconds()*rotation_speed);




        if(Globals::DISTANCE(entity_sprite.getPosition(),path)<5){
            entity_sprite.setRotation(0.0);
            speed_vector.x = 0;
            speed_vector.y = 0;
            in_desired_position = true;
            first_move_check = true;
            speed_vector = sf::Vector2f(0.0,0.0);
        }

    }
    if(falling){
        entity_sprite.setRotation(0.0);

        movement.x = 0;
        movement.y = 0;
        inertial_force.x =0;
        inertial_force.y =0;
        if(entity_sprite.getScale().x >=0 || entity_sprite.getScale().y >=0 )
            entity_sprite.setScale(std::abs(entity_sprite.getScale().x-10*time.asSeconds()),std::abs(entity_sprite.getScale().x-10*time.asSeconds()));
    }
    if(inertial_force.x !=0 || inertial_force.y != 0){

        if(inertial_force.x > 0)
            inertial_force.x -= std::abs(inertial_force.x*time.asSeconds());
        if(inertial_force.x < 0)
            inertial_force.x += std::abs(inertial_force.x*time.asSeconds());
        if(inertial_force.y > 0)
            inertial_force.y -= std::abs(inertial_force.y*time.asSeconds());
        if(inertial_force.y < 0)
            inertial_force.y += std::abs(inertial_force.y*time.asSeconds());

        //movement.x += inertial_force.x*time.asSeconds();
        //movement.y += inertial_force.y*time.asSeconds();

        //hyper speedfix
        if(std::abs(inertial_force.x) < .25 || (temp_inert.x > 0 && movement.x < 0) || (temp_inert.x < 0 && movement.x > 0)){
            inertial_force.x = 0;
        }
        if(std::abs(inertial_force.y) < .25 || (temp_inert.y > 0 && movement.y<0) || (temp_inert.y < 0 && movement.y > 0)){
            inertial_force.y = 0;
        }
    }

        entity_sprite.move(movement+inertial_force);


        if(std::abs(entity_sprite.getPosition().x-path.x)<.01 || (temp.x > 0 && movement.x<0) || (temp.x < 0 && movement.x > 0)){
            speed_vector.x = 0;
        }
        if(std::abs(entity_sprite.getPosition().y-path.y)<.01 || (temp.y > 0 && movement.y<0) || (temp.y < 0 && movement.y > 0)){
            speed_vector.y = 0;
        }
        temp = movement;
}

void Entity::Bump(sf::Vector2f position_of_bump){

        float lenght = Globals::DISTANCE(entity_sprite.getPosition()-position_of_bump,sf::Vector2f(0.0,0.0));

        inertial_force.x = ((entity_sprite.getPosition().x-position_of_bump.x)/lenght)*push_factor;
        inertial_force.y = ((entity_sprite.getPosition().y-position_of_bump.y)/lenght)*push_factor;
        entity_sprite.setRotation(0.0);
        speed_vector = sf::Vector2f(0.0,0.0);
        temp_inert = inertial_force;
}

void Entity::ResetPath(){
    entity_sprite.setRotation(0.0);
    in_desired_position = true;
    first_move_check = true;
}
sf::Vector2f Entity::GetScale(){
    return entity_sprite.getScale();
}

bool Entity::GetMovable(){
    return movable;
}

void Entity::Animate(){
    if(idle_anim.getElapsedTime().asSeconds() >.75 && std::rand()%2){
        idle_anim.restart();
        sf::IntRect rect = entity_sprite.getTextureRect();
        if(progress_animation){
            rect.left += 16.0;
            if(rect.left == 32.0)
                progress_animation = false;
        }
        else{
            rect.left -= 16.0;
            if(rect.left == 0.0)
                progress_animation = true;
        }
        entity_sprite.setTextureRect(rect);
    }
}
