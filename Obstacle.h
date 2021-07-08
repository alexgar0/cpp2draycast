#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Math.h"

class Obstacle {
public:
    Obstacle(sf::Vector2f first, sf::Vector2f second);
    Obstacle();
    void draw(sf::RenderWindow &window);
    sf::Vector2f findCollisionWith(Obstacle other);
    sf::Vertex line[2];
    float angle;

    void setAngleAndLength(float a, float len);

    float static distanceBetween(sf::Vector2f pos1, sf::Vector2f pos2){
        auto dX = pos1.x - pos2.x;
        auto dY = pos1.y - pos2.y;
        return sqrt(dX*dX + dY*dY);
    };
private:

};

