#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Globals{
public:
    static float SCALE;
    static float DISTANCE(sf::Vector2f a,sf::Vector2f b);
    static bool FILEEXISTS (const std::string& name);
};
