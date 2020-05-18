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
#include <iostream>



int main(){
    srand(time(NULL));
//declaring starting states and objects
    sf::RenderWindow game_window(sf::VideoMode(1200,860),"Shack Indev");
    sf::View game_view(sf::Vector2f(0.0,0.0),static_cast<sf::Vector2f>(game_window.getSize()));
    Map level;
    level.Generate();
    Player player(level);

    //game loop
    while(game_window.isOpen()){
        game_window.clear();
        sf::Event user_event;

        while(game_window.pollEvent(user_event)){
            //closing game when window is closed
            if(user_event.type == sf::Event::Closed){
                game_window.close();
            }
            // catch the resize events
            if (user_event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, user_event.size.width, user_event.size.height);
                game_window.setView(sf::View(visibleArea));
            }
        }


//getting input and updating game
//        player.Interact(level);

//centering view on character
        game_view.setCenter(0.0,0.0);
        game_view.move(player.GetCenter());
        game_window.setView(game_view);


//displaying everything

        game_window.draw(level);
        game_window.draw(player);
        game_window.display();

    }


return 0;
}
