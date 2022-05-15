#include "blade.h"

Blade::Blade(Vector2f startPosition){
    blade.setSize(Vector2f(15, 90));
    blade.setPosition(startPosition);
}

Vector2f Blade::getPosition(){
    return position;
}

Vector2f Blade::setPosition(Vector2f newPosition){
    position = newPosition;
}

RectangleShape Blade::getShape(){
    return blade;
}

void Blade::update(){
    blade.setPosition(position);
}