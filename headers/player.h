#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H

#include <string>

class Player{

private:
    static int nextId;
    int id, highScore;
    std::string name;


public:
    Player();

    explicit Player(std::string Name);

    void setHighScore(int newScore);

    int getHighScore();

};

#endif //MAIN_CPP_PLAYER_H
