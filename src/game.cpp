#include "game.h"

void Game::mainLoop(){

    Clock clock;

    while(screen.window.isOpen()){

        if(screen.currentGameState != GameScreen::GameState::INITIAL) {

            Time dt = clock.restart();

            if (screen.currentGameState == GameScreen::GameState::PAUSED) {
                screen.input();

                sleep(milliseconds(2));
                continue;
            }

            screen.timeSinceLastMove += dt;

            screen.input();
            screen.updateBall();
            screen.draw();
        }
        else{
            screen.StartMenu();
            screen.input();
        }
    }
}