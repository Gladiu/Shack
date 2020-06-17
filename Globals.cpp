#include "Globals.hpp"
#include <cmath>

float Globals::SCALE = 5.0;

float Globals::DISTANCE(sf::Vector2f a,sf::Vector2f b){
    return std::sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}


