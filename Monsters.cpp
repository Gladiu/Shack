#include "Monsters.hpp"
#include "Player.hpp"
#include "Globals.hpp"
#include <iostream>

Monsters::Monsters(){
   std::cout<<"Loading Monster assets..."<<std::endl;
   this->boom_texture.loadFromFile("textures/boom.png");
   boom_texture.setRepeated(true);
   this->boom_texture_ptr = std::make_shared<sf::Texture>(boom_texture);

}

void Monsters::Update(sf::Time time,sf::Vector2f render_center, float render_distance){
    for(unsigned long long i = 0; i <boomers.size(); i++){
        boomers[i].Update(time);
        if(boomers[i].IsFalling() && (std::abs(boomers[i].GetScale().x) <= 1 || std::abs(boomers[i].GetScale().y) <= 1)){
            boomers.erase(boomers.begin()+i);
        }
        if(Globals::DISTANCE(boomers[i].GetPosition(),render_center) < render_distance){
            for(unsigned long long j = 0; j <boomers.size(); j++){
                if(i != j && boomers[i].GetGlobalBounds().intersects(boomers[j].GetGlobalBounds())){
                    boomers[i].Bump(boomers[j].GetPosition());
                    boomers[j].Bump(boomers[i].GetPosition());
                }
            }
        }
        //it.Animate();
    }

}

void Monsters::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    for(auto &it:boomers)
        target.draw(it,states);
}

void Monsters::Generate(const std::vector<sf::Vector2f> & legal_positions){
    Boom andrzej;
    andrzej.SetTexture(boom_texture_ptr);
    for(auto &it :legal_positions){
        if(std::rand()%25 == 1){
            andrzej.SetPosition(it);
            boomers.emplace_back(andrzej);
        }
    }
}

bool Monsters::AreClicked(sf::Vector2f position){
    bool anwser = false;
    for(unsigned long long i = 0; i <boomers.size(); i++){
        if(Globals::DISTANCE(boomers[i].GetPosition(),position)<20*Globals::SCALE){
            boomers[i].Bump(position);
        }
    }
    return anwser;
}


void Monsters::Interact(Player &player){
    for(auto &it:boomers){

        if(Globals::DISTANCE(it.GetPosition(),player.GetPosition())< 350)
            it.SetPath(player.GetPosition());
        if(it.GetGlobalBounds().intersects(player.GetGlobalBounds())){
            player.Bump(it.GetPosition());
            it.Bump(player.GetPosition());
            //it.ResetPath();
        }
    }
}
