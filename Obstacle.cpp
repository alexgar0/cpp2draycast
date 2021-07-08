//
// Created by ALEXG on 06.07.2021.
//

#include <iostream>
#include <cmath>
#include "Obstacle.h"


Obstacle::Obstacle(sf::Vector2f first, sf::Vector2f second) {
    line[0].position = first;
    line[1].position = second;
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;
}

void Obstacle::draw(sf::RenderWindow &window) {
    window.draw(line, 2, sf::Lines);

}

sf::Vector2f Obstacle::findCollisionWith(Obstacle other) {
    auto a1 = this->line[1].position.y - this->line[0].position.y;
    auto b1 = this->line[0].position.x - this->line[1].position.x;
    auto c1 =
            -this->line[0].position.x * this->line[1].position.y + this->line[0].position.y * this->line[1].position.x;

    auto a2 = other.line[1].position.y - other.line[0].position.y;
    auto b2 = other.line[0].position.x - other.line[1].position.x;
    auto c2 =
            -other.line[0].position.x * other.line[1].position.y + other.line[0].position.y * other.line[1].position.x;

    auto colX = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
    auto colY = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);

    if ((!((colX > other.line[0].position.x && colX < other.line[1].position.x ||
            colX < other.line[0].position.x && colX > other.line[1].position.x) && colY > other.line[0].position.y &&
           colY < other.line[1].position.y) && !(colY < other.line[0].position.y && colY > other.line[1].position.y)) ||
        !((colX > this->line[0].position.x) == (this->line[1].position.x > this->line[0].position.x) &&
          (colY > this->line[0].position.y) == (this->line[1].position.y > this->line[0].position.y))) {
        {
            colX = 0;
            colY = 0;
        }
    }


    return sf::Vector2f(colX, colY);
}

Obstacle::Obstacle() : Obstacle(sf::Vector2f(0, 0), sf::Vector2f(0, 0)) {

}

void Obstacle::setAngleAndLength(float a, float len) {
    this->angle = a;
    auto x1 = len * cos(angle);
    auto y1 = len * sin(angle);
    this->line[1].position = sf::Vector2f(x1, y1);

}



