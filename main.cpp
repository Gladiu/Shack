#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Globals.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Background.hpp"
#include "Monsters.hpp"
#include "Menu.hpp"
#include <iostream>



int main(){
    srand(time(NULL));
    sf::RenderWindow game_window(sf::VideoMode(1200,900),"Shack");
    game_window.setKeyRepeatEnabled(true);
    sf::Font score_font;
    score_font.loadFromFile("textures/font.TTF");
    bool quit = false;
    int enemies_left;
    int n_of_last_level =1;
    while(game_window.isOpen()){
        {
            Menu mainmenu;
            //declaring starting states and objects
            sf::Vector2f mouse_position;
            bool left_mbtn_is_hold = false;
            game_window.setFramerateLimit(120);
            sf::View game_view(sf::Vector2f(0.0,0.0),static_cast<sf::Vector2f>(game_window.getSize()));
            sf::View static_view = game_view;
            Map level;
            Background stars;
            Player player;
            sf::Clock clock;
            sf::Time elapsed;
            Monsters enemies;
            sf::Text score;
            score.setFont(score_font);
            sf::Music music,ambient;
            music.openFromFile("sounds/soundtrack.wav");
            ambient.openFromFile("sounds/ambient.wav");
            ambient.setLoop(true);
            music.setLoop(true);
            music.play();
            stars.UpdateRenderCenter(sf::Vector2f(0.0,0.0));
            stars.SetRenderDistance(100000.0);
            while(!quit){
                game_window.clear();
                sf::Event user_event;
                mouse_position = game_window.mapPixelToCoords(sf::Mouse::getPosition(game_window));
                while(game_window.pollEvent(user_event)){

                    //closing game when window is closed
                    if(user_event.type == sf::Event::Closed){
                        game_window.close();
                        quit = true;
                    }

                    // catch the resize events
                    if (user_event.type == sf::Event::Resized)
                    {
                        sf::FloatRect visibleArea(0.f, 0.f, user_event.size.width, user_event.size.height);
                        game_view = sf::View(visibleArea);
                        static_view.setSize(user_event.size.width, user_event.size.height);
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        mainmenu.Interact(mouse_position,true);

                    }
                }

                if(mainmenu.GetContinueGame()){
                    quit = true;
                }
                if(mainmenu.GetExitGame()){
                    quit = true;
                    game_window.close();
                }

                game_window.setView(static_view);
                stars.Proces(elapsed);
                game_window.draw(stars);


                game_view.setCenter(0.0,0.0);
                game_window.setView(game_view);
                mainmenu.Interact(mouse_position,false);
                game_window.draw(mainmenu);
                game_window.display();
                elapsed = clock.restart();

            }
            quit = false;
            if(game_window.isOpen()){
                if(Globals::FILEEXISTS("levels/"+std::to_string(n_of_last_level)+".txt")){
                    level.GenerateFromFile("levels/"+std::to_string(n_of_last_level)+".txt");
                    n_of_last_level++;
                }
                else
                    level.Generate();
                player.SpawnIn(level);
                //setting render distance and render point
                level.UpdateRenderCenter(player.GetPosition());
                level.SetRenderDistance(Globals::DISTANCE(game_window.getView().getSize(),sf::Vector2f(0.0,0.0)));
                enemies.Generate(level.GetSpawningSpaces());
                enemies_left = enemies.GetSize();
                score.setFillColor(sf::Color(230,178,23,255));
                score.setCharacterSize(30);
                score.setPosition(static_view.getSize().x/4-50,-static_view.getSize().y/4-50);
                stars.SetRenderDistance(Globals::DISTANCE(game_window.getView().getSize(),sf::Vector2f(0.0,0.0)));
                music.setVolume(25);

            }
            music.stop();
            ambient.play();
            //game loop
            while(game_window.isOpen() && player.GetAlive() && enemies_left != 0 ){
                game_window.clear();
                sf::Event user_event;
                //updating clocks
                score.setString("OBJECTIVE "+std::to_string(enemies_left));
                elapsed = clock.restart();
                while(game_window.pollEvent(user_event) || left_mbtn_is_hold){

                    //closing game when window is closed
                    if(user_event.type == sf::Event::Closed){
                        game_window.close();
                    }
                    if(user_event.type == sf::Event::MouseButtonReleased){// && user_event.mouseButton.button == sf::Mouse::Left){
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
                        score.setPosition(static_view.getSize().x/4-50,-static_view.getSize().y/4-50);
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
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                        n_of_last_level =1;
                        player.SetAlive(false);
                    }
                    if(left_mbtn_is_hold)
                        break;
                }
                //checking if someone died
                level.CheckIfFalling(player);

                level.CheckIfFalling(enemies.members);
                //std::cout<<1/elapsed.asSeconds()<<std::endl; //FPS counter
                //drawing static elements of the game like hud and background
                game_window.setView(static_view);
                stars.Proces(elapsed);
                game_window.draw(stars);

                //getting input and updating game
                player.Update(elapsed);
                player.UpdateAnimation();
                level.UpdateRenderCenter(player.GetPosition());
                enemies.Interact(player);
                enemies.CheckIfDead();
                enemies_left = enemies.Update(elapsed,player.GetPosition(),Globals::DISTANCE(game_view.getSize(),sf::Vector2f(0.0,0.0)));


                //centering view on character
                game_view.setCenter(0.0,0.0);
                game_view.move(player.GetPosition());
                game_window.setView(game_view);


                //displaying everything

                game_window.draw(level);
                game_window.draw(enemies);
                game_window.draw(player);
                game_window.setView(static_view);
                game_window.draw(score);
                game_window.setView(game_view);
                game_window.display();


            }
        }
        if(enemies_left == 0)
            quit = true;
    }

    return 0;
}
