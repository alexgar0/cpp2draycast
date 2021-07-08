#pragma once


#include "Obstacle.h"

class PlayerRayCaster {
public:
    PlayerRayCaster(float &deltaTime);
    explicit PlayerRayCaster(sf::Vector2f startPos, float &deltaTime);
    sf::Vector2f position;

    void translate(sf::Vector2f direction);
    void update();
    void draw(sf::RenderWindow &window);
    void lookOn(sf::Vector2f lookingPoint);
    sf::Vector2f getMovementVector();
private:
    float &deltaTime;
    float const defRayLen = 10000.f;
    float angle;
    float speed;
    sf::CircleShape shape;
    sf::CircleShape testShape;
    std::vector<Obstacle> obstacles;
    std::vector<Obstacle> rays;

    void drawRays(sf::RenderWindow &window);
    void initRays(int rayCount);

    void initObstacleRand(int obstacleCount);
    void initRayWithAngle(float a);
    void updateRays();


};
