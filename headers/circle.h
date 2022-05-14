#ifndef MAIN_CPP_CIRCLE_H
#define MAIN_CPP_CIRCLE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Circle{

private:
    Vector2f position;
    CircleShape circle;

public:

    explicit Circle(Vector2f startPosition);

    Vector2f getPosition();

    void setPosition(Vector2f newPosition);

    CircleShape getShape();

    void update();

    friend class GameScreen;

};


#endif //MAIN_CPP_CIRCLE_H
