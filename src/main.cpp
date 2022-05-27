#include "../headers/game.h"
#include <windows.h>

int main() {

	ShowWindow(GetConsoleWindow(), SW_HIDE);

    Game PongGame;

    PongGame.mainLoop();

    return 0;
}
