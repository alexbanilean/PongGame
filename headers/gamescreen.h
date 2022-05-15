#ifndef MAIN_CPP_GAMESCREEN_H
#define MAIN_CPP_GAMESCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "player.h"
#include "circle.h"
#include "blade.h"
#include "wall.h"
#include "highscoretable.h"
#include <deque>

using namespace sf;
using namespace std;

class GameScreen{

private:
    // Window
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60; // frames per second

    Color backgroundColor = Color(65, 75, 80);
    Color displayColor = Color(90, 200, 230);

    Player player1, player2;
    int score1, score2;

    RectangleShape line;

    Circle ball = Circle(Vector2f(600, 400));
    int ballDirection, ballSpeed;
    int blade1Direction, blade2Direction, bladeSpeed;

    Blade blade1 = Blade(Vector2f(50, 400));
    Blade blade2 = Blade(Vector2f(1150, 400));

    vector<Wall> walls;

    Time timeSinceLastMove, timeSinceBladesMove;

    int currentGameState, lastGameState;
    bool displayHighscoresTable;

    HighScoreTable table;

public:

    enum Direction { UP, RIGHT, DOWN, LEFT, UPRIGHT, DOWNRIGHT, UPLEFT, DOWNLEFT };
    enum GameState { RUNNING, PAUSED, INITIAL, READING, DISPLAY};

    GameScreen();

    void StartMenu();

    void read();

    void input();

    void updateBall();
    void updateBlades();

    void startTheGame();
    void togglePause();

    void draw();
    void drawInstructions();
    void drawHighscoresTable();

    friend class Game;

};

#endif //MAIN_CPP_GAMESCREEN_H
