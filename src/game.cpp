#include "game.h"

void Game::mainLoop(){

	Clock clock;

	while(screen.window.isOpen()){
		Time dt = clock.restart();

		screen.timeSinceLastMove += dt;
		screen.timeSinceBladesMove += dt;

		if(screen.currentGameState == GameScreen::GameState::INITIAL){
			screen.StartMenu();
			screen.input();
		} else if(screen.currentGameState == GameScreen::GameState::PAUSED){
			screen.draw();
			screen.input();

			sleep(milliseconds(2));
		} else if(screen.currentGameState == GameScreen::GameState::READING){
			screen.read();
		} else if(screen.currentGameState == GameScreen::GameState::DISPLAY){
			if(!screen.displayHighscoreTable)
				screen.drawInstructions();
			else
				screen.drawHighscoreTable();

			screen.input();
		} else{
			// RUNNING state

			screen.updateBall();
			screen.updateBlades();

			screen.draw();
			screen.input();
		}

	}
}