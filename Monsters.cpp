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
   robot_hit_bfr.loadFromFile("sounds/robot.wav");
   robot_hit.setBuffer(robot_hit_bfr);
   robot_hit.setVolume(75);

   boom_hit_bfr.loadFromFile("sounds/boom.wav");
   boom_hit.setBuffer(boom_hit_bfr);
   boom_hit.setVolume(50);

   boom_death_snd_bfr.loadFromFile("sounds/boom_falling.wav");
   boom_death.setBuffer(boom_death_snd_bfr);
   robot_death_snd_bfr.loadFromFile("sounds/robot_falling.wav");
   robot_death.setBuffer(robot_death_snd_bfr);


   robot_hit_sound_cooldown.restart();
}
Monsters::~Monsters(){
    members.clear();

}

int Monsters::Update(sf::Time time,sf::Vector2f render_center, float render_distance){
    for(unsigned long long i = 0; i <members.size(); i++){
        if(Globals::DISTANCE(members[i].GetPosition(),render_center) < render_distance){
            members[i].Update(time);
            members[i].Animate();


            for(unsigned long long j = 0; j <members.size(); j++){
                if(i != j && members[i].GetGlobalBounds().intersects(members[j].GetGlobalBounds()) && robot_hit_sound_cooldown.getElapsedTime().asSeconds()>.2){
                    members[i].Bump(members[j].GetPosition());
                    members[j].Bump(members[i].GetPosition());
                    if(members[i].GetMovable() || members[j].GetMovable())
                        robot_hit.play();
                    if(!members[i].GetMovable() || !members[j].GetMovable())
                        boom_hit.play();
                    robot_hit_sound_cooldown.restart();
                }
            }
            if(members[i].IsFalling() && (std::abs(members[i].GetScale().x) <= .5 || std::abs(members[i].GetScale().y) <= .5)){
                if(members[i].GetMovable()){
                    robot_death.play();
                    std::cout<<"a";
                }
                if(!members[i].GetMovable())
                    boom_death.play();
                members.erase(members.begin()+i);
            }
        }
    }
    return members.size();
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
    members.clear();
    for(unsigned long long i =0 ;i<legal_positions.size();i++){
        if(std::rand()%25 == 1){
            if(counter <=2){
                marek.SetPosition(legal_positions[i]);
                members.emplace_back(marek);

                counter++;
            }
            else{
                andrzej.SetPosition(legal_positions[i]);
                members.push_back(andrzej);
                counter =1;
            }
        }
    }
    marek.SetPosition(legal_positions[legal_positions.size()-1]);
    members.emplace_back(marek);

}

bool Monsters::AreClicked(sf::Vector2f position){
    bool anwser = false;
    for(auto & it:members){
        if( it.GetMovable() && Globals::DISTANCE(it.GetPosition(),position)<20*Globals::SCALE){
            it.Bump(position);
            if(robot_hit_sound_cooldown.getElapsedTime().asSeconds()>.2){
                robot_hit.play();
                robot_hit_sound_cooldown.restart();
            }
        }
    }
    return anwser;
}


void Monsters::Interact(Player &player){
    if(!player.IsFalling()){
        for(auto &it:members){

            if(!it.GetMovable() && Globals::DISTANCE(it.GetPosition(),player.GetPosition())< 350)
                it.SetPath(player.GetPosition());
            if(it.GetGlobalBounds().intersects(player.GetGlobalBounds())){
                if(it.GetMovable()){
                    it.Bump(player.GetPosition());
                }
                else{
                    player.Bump(it.GetPosition());
                }
                if(robot_hit_sound_cooldown.getElapsedTime().asSeconds()>.2){
                    if(it.GetMovable())
                        robot_hit.play();
                    else
                        boom_hit.play();
                    robot_hit_sound_cooldown.restart();
                }

            }
        }
    }
}

int Monsters::GetSize(){
    return members.size();
}
