#ifndef MAIN_CPP_GAMESCREEN_H
#define MAIN_CPP_GAMESCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "player.h"
#include "circle.h"
#include "blade.h"
#include "wall.h"
#include <deque>

using namespace sf;
using namespace std;

class GameScreen{

private:
    // Window
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    Player player1, player2;
    int score1, score2;

    Circle ball = Circle(Vector2f(600, 400));
    int ballDirection, ballSpeed;
    deque<int> directionQueue;

    Blade blade1 = Blade(Vector2f(50, 400));
    Blade blade2 = Blade(Vector2f(1150, 400));

    vector<Wall> walls;

    Time timeSinceLastMove;

    int currentGameState, lastGameState;


public:

    enum Direction { UP, RIGHT, DOWN, LEFT, UPRIGHT, DOWNRIGHT, UPLEFT, DOWNLEFT };
    enum GameState { RUNNING, PAUSED, INITIAL};

    GameScreen();

    void StartMenu();

    void read();

    void input();

    void addDirection(int newDirection);
    void updateBall();

    void startTheGame();
    void togglePause();

    void draw();
    void drawHighscoresTable();

    friend class Game;

};

#endif //MAIN_CPP_GAMESCREEN_H
