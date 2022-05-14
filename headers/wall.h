#ifndef MAIN_CPP_WALL_H
#define MAIN_CPP_WALL_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Wall{

private:
    RectangleShape wallShape;

public:
    Wall(Vector2f position, Vector2f size);

    RectangleShape getShape();

};


#endif //MAIN_CPP_WALL_H
