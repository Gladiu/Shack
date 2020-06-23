#include "Globals.hpp"
#include <cmath>
#include <fstream>

float Globals::SCALE = 5.0;

float Globals::DISTANCE(sf::Vector2f a,sf::Vector2f b){
    return std::sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

bool Globals::FILEEXISTS(const std::string& name) {
    std::fstream f(name.c_str());
    return f.good();
}


