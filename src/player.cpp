#include "player.h"

int Player::nextId = 1;

Player::Player(){
	id = highScore = 0;
	name = "";
}

Player::Player(std::string Name){
	id = nextId++;
	highScore = 0;
	name = Name;
}

void Player::setHighScore(int newScore){
	highScore = newScore;
}

int Player::getHighScore() const{
	return highScore;
}

int Player::getId() const{
	return id;
}

void Player::setName(std::string Name){
	name = Name;
}

std::string Player::getName(){
	return name;
}