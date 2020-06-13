#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Map.hpp"
#include "Room.hpp"
#include "Corridor.hpp"
#include "Globals.hpp"
#include "Background.hpp"
#include <iostream>



int main(){
    srand(time(NULL));
    //declaring starting states and objects
    sf::Vector2f mouse_position;
    sf::RenderWindow game_window(sf::VideoMode(1200,860),"Shack Indev");
    sf::View game_view(sf::Vector2f(0.0,0.0),static_cast<sf::Vector2f>(game_window.getSize()));
    sf::View static_view = game_view;
    Map level;
    Background stars;
    level.Generate();
    Player player(level);
    sf::Clock clock;
    sf::Time elapsed;


    //game loop
    while(game_window.isOpen()){
        game_window.clear();
        sf::Event user_event;
        //updating clocks
        elapsed = clock.restart();
        while(game_window.pollEvent(user_event)){

            //closing game when window is closed
            if(user_event.type == sf::Event::Closed){
                game_window.close();
            }
            // catch the resize events
            if (user_event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.f, 0.f, user_event.size.width, user_event.size.height);
                game_view = sf::View(visibleArea);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                //handling actions of character

                // get the current mouse position in the window
                sf::Vector2i temp;
                temp = sf::Mouse::getPosition(game_window);
                // convert it to world coordinates
                mouse_position = game_window.mapPixelToCoords(temp);
                player.SetPath(mouse_position);
            }
        }
//checking if someone died
        if(level.IsEmpty(player.GetGlobalBounds())){
            player.IsFalling(true);
        }
        std::cout<<1/elapsed.asSeconds()<<std::endl;
//drawing static elements of the game like hud and background
        game_window.setView(static_view);
        stars.Proces(elapsed);
        game_window.draw(stars);

//getting input and updating game
        player.Update(elapsed);
//centering view on character
        game_view.setCenter(0.0,0.0);
        game_view.move(player.GetPosition());
        game_window.setView(game_view);


//displaying everything
        game_window.draw(level);
        game_window.draw(player);
        game_window.display();


    }


return 0;
}
