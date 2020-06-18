#include "Monsters.hpp"
#include "Globals.hpp"
#include <iostream>

Monsters::Monsters(){
   std::cout<<"Loading Monster assets..."<<std::endl;
   this->boom_texture.loadFromFile("textures/boom.png");
   boom_texture.setRepeated(true);
   this->boom_texture_ptr = std::make_shared<sf::Texture>(boom_texture);
   this->robot_texture.loadFromFile("textures/robot.png");
   robot_texture.setRepeated(true);
   this->robot_texture_ptr = std::make_shared<sf::Texture>(robot_texture);

}

void Monsters::Update(sf::Time time,sf::Vector2f render_center, float render_distance){
    for(unsigned long long i = 0; i <members.size(); i++){
        if(Globals::DISTANCE(members[i].GetPosition(),render_center) < render_distance){
            members[i].Update(time);
            members[i].Animate();
            if(members[i].IsFalling() && (std::abs(members[i].GetScale().x) <= 1 || std::abs(members[i].GetScale().y) <= 1)){
                members.erase(members.begin()+i);
            }

            for(unsigned long long j = 0; j <members.size(); j++){
                if(i != j && members[i].GetGlobalBounds().intersects(members[j].GetGlobalBounds())){
                    members[i].Bump(members[j].GetPosition());
                    members[j].Bump(members[i].GetPosition());
                }
            }
        }
    }

}

void Monsters::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    for(auto &it:members)
        target.draw(it,states);
}

void Monsters::Generate(const std::vector<sf::Vector2f> & legal_positions){
    Boom andrzej;
    andrzej.SetTexture(boom_texture_ptr);
    Robot marek;
    marek.SetTexture(robot_texture_ptr);
    int counter =1;
    for(unsigned long long i =0 ;i<legal_positions.size();i++){
        if(std::rand()%25 == 1){
            if(counter <=2){
                andrzej.SetPosition(legal_positions[i]);
                members.emplace_back(andrzej);
                counter++;
            }
            else{
                marek.SetPosition(legal_positions[i]);
                members.emplace_back(marek);
                counter =1;
            }
        }
    }
}

bool Monsters::AreClicked(sf::Vector2f position){
    bool anwser = false;
    for(auto & it:members){
        if( it.GetMovable() && Globals::DISTANCE(it.GetPosition(),position)<20*Globals::SCALE)
            it.Bump(position);
    }
    return anwser;
}


void Monsters::Interact(Player &player){
    if(!player.IsFalling()){
        for(auto &it:members){

            if(!it.GetMovable() && Globals::DISTANCE(it.GetPosition(),player.GetPosition())< 350)
                it.SetPath(player.GetPosition());
            if(it.GetGlobalBounds().intersects(player.GetGlobalBounds())){
                if(it.GetMovable())
                    it.Bump(player.GetPosition());
                else
                    player.Bump(it.GetPosition());

            }
        }
    }
}
