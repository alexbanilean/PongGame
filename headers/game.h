#ifndef MAIN_CPP_GAME_H
#define MAIN_CPP_GAME_H

#include "gamescreen.h"

using namespace std;

class Game{

private:
	GameScreen screen;

public:
	void mainLoop();
};

#endif //MAIN_CPP_GAME_H
