#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Globals.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include "Room.hpp"
#include "Player.hpp"
#include "Corridor.hpp"
#include "Background.hpp"
#include "Boom.hpp"
#include "Monsters.hpp"
#include <iostream>



int main(){
    srand(time(NULL));
    //declaring starting states and objects
    sf::Vector2f mouse_position;
    bool left_mbtn_is_hold = false;
    sf::RenderWindow game_window(sf::VideoMode(1200,860),"Shack Alpha");
    sf::View game_view(sf::Vector2f(0.0,0.0),static_cast<sf::Vector2f>(game_window.getSize()));
    sf::View static_view = game_view;
    Map level;
    Background stars;
    level.Generate();
    Player player;
    player.SpawnIn(level);
    sf::Clock clock;
    sf::Time elapsed;


    //setting render distance and render point
    level.UpdateRenderCenter(player.GetPosition());
    level.SetRenderDistance(Globals::DISTANCE(game_window.getView().getSize(),sf::Vector2f(0.0,0.0)));

    Monsters enemies;
    enemies.Generate(level.GetSpawningSpaces());    enemies.Generate(level.GetSpawningSpaces());

    stars.UpdateRenderCenter(sf::Vector2f(0.0,0.0));
    stars.SetRenderDistance(Globals::DISTANCE(game_window.getView().getSize(),sf::Vector2f(0.0,0.0)));

    //game loop
    while(game_window.isOpen()){
        game_window.clear();
        sf::Event user_event;
        //updating clocks
        elapsed = clock.restart();
        while(game_window.pollEvent(user_event) || left_mbtn_is_hold){

            //closing game when window is closed
            if(user_event.type == sf::Event::Closed){
                game_window.close();
            }
            if(user_event.type == sf::Event::MouseButtonReleased && user_event.mouseButton.button == sf::Mouse::Left){
                left_mbtn_is_hold = false;
            }
            // catch the resize events
            if (user_event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.f, 0.f, user_event.size.width, user_event.size.height);
                game_view = sf::View(visibleArea);
                static_view.setSize(user_event.size.width, user_event.size.height);
                level.SetRenderDistance(Globals::DISTANCE(game_view.getSize(),sf::Vector2f(0.0,0.0)));
                stars.SetRenderDistance(Globals::DISTANCE(game_view.getSize(),sf::Vector2f(0.0,0.0)));
            }
            if (left_mbtn_is_hold || sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //handling actions of character

                // get the current mouse position in the window
                sf::Vector2i temp;
                temp = sf::Mouse::getPosition(game_window);
                mouse_position = game_window.mapPixelToCoords(temp);
                // convert it to world coordinates
                player.SetPath(mouse_position);
                left_mbtn_is_hold = true;

            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                sf::Vector2i temp;
                temp = sf::Mouse::getPosition(game_window);
                mouse_position = game_window.mapPixelToCoords(temp);
                player.UsedForceAt(mouse_position);
                enemies.AreClicked(mouse_position);
            }
            if(left_mbtn_is_hold)
                break;
        }
//checking if someone died
        level.CheckIfFalling(player);

        level.CheckIfFalling(enemies.boomers);
        std::cout<<1/elapsed.asSeconds()<<std::endl;
//drawing static elements of the game like hud and background
        game_window.setView(static_view);
        stars.Proces(elapsed);
        game_window.draw(stars);

//getting input and updating game
        player.Update(elapsed);
        player.UpdateAnimation();
        level.UpdateRenderCenter(player.GetPosition());
        enemies.Interact(player);
        enemies.Update(elapsed,player.GetPosition(),Globals::DISTANCE(game_view.getSize(),sf::Vector2f(0.0,0.0)));


//centering view on character
        game_view.setCenter(0.0,0.0);
        game_view.move(player.GetPosition());
        game_window.setView(game_view);


//displaying everything

        game_window.draw(level);
        game_window.draw(enemies);
        game_window.draw(player);
        game_window.display();


    }


return 0;
}
