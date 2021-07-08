

#include <iostream>
#include "PlayerRayCaster.h"
#include "Math.h"

void PlayerRayCaster::translate(sf::Vector2f direction) {
    this->position += direction;
    for (auto &ray : this->rays) {
        ray.line[1].position += direction;
    }
}

PlayerRayCaster::PlayerRayCaster(sf::Vector2f startPos, float &deltaTime) : deltaTime(deltaTime) {
    this->position = startPos;
    this->speed = 1000.f;
    this->angle = 0.f;
    this->shape = sf::CircleShape(10);
    this->shape.setPosition(startPos);
    this->shape.setFillColor(sf::Color::Black);
    this->shape.setOrigin(this->shape.getRadius(), this->shape.getRadius());
    this->initRays(100);
//    this->obstacles.push_back(Obstacle(sf::Vector2f(1000, 400), sf::Vector2f(700, 15)));
//    this->obstacles.push_back(Obstacle(sf::Vector2f(0, 400), sf::Vector2f(1000, 700)));
    this->initObstacleRand(3);
}

PlayerRayCaster::PlayerRayCaster(float &deltaTime) : PlayerRayCaster(sf::Vector2f(0.f, 0.f), deltaTime) {

}

void PlayerRayCaster::update() {
    this->translate(this->getMovementVector() * deltaTime * this->speed);
    this->shape.setPosition(this->position);
    this->updateRays();

}

sf::Vector2f PlayerRayCaster::getMovementVector() {
    sf::Vector2f moveVector = sf::Vector2f(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        moveVector += sf::Vector2f(0, -1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        moveVector += sf::Vector2f(1, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        moveVector += sf::Vector2f(0, 1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        moveVector += sf::Vector2f(-1, 0);

    auto vecLen = 0.f;
    if (moveVector.x != 0 || moveVector.y != 0)
        vecLen = 1 / sqrt(pow(moveVector.x, 2) + pow(moveVector.y, 2));
    return sf::Vector2f(moveVector.x * vecLen, moveVector.y * vecLen);
}

void PlayerRayCaster::draw(sf::RenderWindow &window) {
    window.draw(this->shape);
    window.draw(this->testShape);
    for (int i = 0; i < this->obstacles.size(); i++)
        obstacles[i].draw(window);
    this->drawRays(window);
}

void PlayerRayCaster::drawRays(sf::RenderWindow &window) {

    if (!this->rays.empty()) {
        sf::Vertex line[2];
        for (auto &ray : this->rays) {
            ray.draw(window);
        }
    }

}

void PlayerRayCaster::updateRays() {
    if (!this->rays.empty()) {
        auto delta_angle = rays[0].angle - this->angle;
        for (auto &ray : this->rays) {
            ray.line[0].position = this->position;
            ray.setAngleAndLength(ray.angle - delta_angle, defRayLen);

            bool isCollided = false;

            if (!this->obstacles.empty()) {
                auto minDist = defRayLen;
                auto targetPoint = sf::Vector2f(0,0);
                for (auto &obstacle : this->obstacles) {
                    auto collisionPoint = ray.findCollisionWith(obstacle);
                    if(collisionPoint.x!=0 && collisionPoint.y!=0){
                        isCollided = true;
                        auto distance = Obstacle::distanceBetween(ray.line[0].position, collisionPoint);
                        if (distance<minDist) {
                            minDist = distance;
                            targetPoint = collisionPoint;
                        }
                    }

                }
                if(isCollided)
                    ray.line[1].position = targetPoint;
            }
        }

    }
}

void PlayerRayCaster::initRayWithAngle(float a) {
    auto ray = Obstacle();
    ray.line[0].position = this->position;
    ray.setAngleAndLength(a, this->defRayLen);
    rays.push_back(ray);

}

void PlayerRayCaster::initRays(int rayCount) {

    auto deltaAngle = 2.f / (float) rayCount * M_PI;
    auto currentAngle = 0.f;

    for(int i = 0; i<rayCount; i++){
        this->initRayWithAngle(currentAngle + this->angle);
        this->rays.back().angle = currentAngle + this->angle;
        currentAngle += deltaAngle;
    }

}

void PlayerRayCaster::lookOn(sf::Vector2f lookingPoint) {
    this->angle = std::atan((this->position.y - lookingPoint.y) / (this->position.x - lookingPoint.x)) ;
    // std::cout << this->angle <<" " << (this->position.y - lookingPoint.y) / (this->position.x - lookingPoint.x) << "\n";
}

void PlayerRayCaster::initObstacleRand(int obstacleCount) {
    for(int i = 0; i<obstacleCount; i++){
        auto pos1 = sf::Vector2f (rand() % 1280, rand() % 720);
        auto pos2 = sf::Vector2f (rand() % 1280, rand() % 720);
        this->obstacles.push_back(Obstacle(pos1, pos2));
    }

}
