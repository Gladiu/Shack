#include "Background.hpp"
#include "Globals.hpp"
#include <iostream>

Background::Background(){
    texture.loadFromFile("textures/stars.png");
    std::shared_ptr<sf::Texture> textptr = std::make_shared<sf::Texture>(texture);
    this->size.y  = 16.0 * Globals::SCALE*40;
    this->size.x = 16.0 * Globals::SCALE*40;
    sf::Vector2f top_left_pos = sf::Vector2f(0.0,0.0);

    //filling room with floor tiles
    bool generating=true;
    sf::Vector2f last_tile_pos = top_left_pos;

    while(generating){
        Tile generated_tile;
        generated_tile.Generate(textptr);
        generated_tile.setTextureRect(sf::IntRect(std::rand()%4*16,0,16,16));
        generated_tile.setPos(last_tile_pos.x,last_tile_pos.y);

        if(last_tile_pos.y < this->size.y)
            last_tile_pos.y += 16.0*Globals::SCALE;
        if(last_tile_pos.y >= this->size.y){
            last_tile_pos.y = 0;
            last_tile_pos.x += 16.0*Globals::SCALE;
        }
        else if(last_tile_pos.x >= this->size.x ){
                generating = false;
            }

        bck_tiles.push_back(generated_tile);
    }
    int i =0;
    for(auto &it:bck_tiles){
        it.setPos(it.GetPosition().x-16.0*Globals::SCALE*25,it.GetPosition().y-16.0*Globals::SCALE*25);
        if(std::rand()%6){
            glowing_tiles.emplace_back(std::pair(i,true));
        }
        i++;
    }
    background_for_tiles = bck_tiles;
    for(auto &it:background_for_tiles){
        it.setTextureRect(sf::IntRect(5*16,0,16,16));
    }
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    for(auto &it : background_for_tiles){
        if(Globals::DISTANCE(it.GetPosition(),render_center) < render_distance)
            target.draw(it,states);
    }
    for(auto &it : bck_tiles){
        if(Globals::DISTANCE(it.GetPosition(),render_center) < render_distance)
            target.draw(it,states);
    }
}

void Background::Proces(sf::Time time){
    for(auto &it:glowing_tiles){
        sf::Color temp = bck_tiles[it.first].getColor();
        if(temp.a<10 && it.second == true){
            it.second = false;
        }
        if(temp.a > 240 && it.second == false){
            it.second = true;
        }
        if(it.second)
            temp.a -= .5;
        else
            temp.a += 1;
        bck_tiles[it.first].SetColor(temp);
    }

}
void Background::UpdateRenderCenter(sf::Vector2f position){
    render_center = position;
}

void Background::SetRenderDistance(float distance){
    render_distance = distance;
}
