#ifndef MAIN_CPP_BLADE_H
#define MAIN_CPP_BLADE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Blade{

private:
	Vector2f position;
	RectangleShape blade;
	int nr_collisions;

public:

	explicit Blade(Vector2f startPosition);

	Vector2f getPosition();

	Vector2f setPosition(Vector2f newPosition);

	RectangleShape getShape();

	void update();

	friend class GameScreen;

};

#endif //MAIN_CPP_BLADE_H
