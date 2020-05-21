#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include <vector>
class Room : public sf::Drawable{
    //exits points must be out of bounds, its where corridor is starting!
    public:
        Room();
        void Generate(sf::Vector2f position,sf::Texture *input_texture,int where);
        sf::Vector2f Get_Top_Left_Corner();
        void Overlap_Fix(const Room &another_room);
        bool Collision_Check(Room another_room);
        bool GetHasExit();
        sf::Vector2f GetValidExit(sf::Vector2f position);
        void AddExit(sf::Vector2f exit);
        sf::Vector2f GetExitPoint();
        void Emplace_Back_Connected_Room_Number(int number);
        sf::Vector2f GenerateLeftExit();
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    private:
        std::vector<Tile> Tiles;
        sf::Vector2f top_left_pos;
        sf::Vector2f size;
        bool has_exit;
        std::vector <sf::Vector2f> ExitPos;
        std::vector < int > Connected_to_room;

};
