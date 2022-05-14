#include "player.h"

int Player::nextId = 1;

Player::Player(){
    id = highScore = 0;
    name = "";
}

Player::Player(std::string Name){
    id = nextId++;
    name = Name;
}

void Player::setHighScore(int newScore){
    highScore = newScore;
}

int Player::getHighScore(){
    return highScore;
}