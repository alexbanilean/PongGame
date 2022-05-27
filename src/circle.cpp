#include "circle.h"

Circle::Circle(Vector2f startPosition){
	circle.setRadius(10);
	circle.setPosition(startPosition);
	position = startPosition;
}

Vector2f Circle::getPosition(){
	return position;
}

void Circle::setPosition(Vector2f newPosition){
	position = newPosition;
}

CircleShape Circle::getShape(){
	return circle;
}

void Circle::update(){
	circle.setPosition(position);
}