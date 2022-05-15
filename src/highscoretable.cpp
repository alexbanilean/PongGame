#include "highscoretable.h"
#include "algorithm"
#include "iostream"

HighScoreTable::HighScoreTable(){
    highscores = {};
}

std::vector<Score> HighScoreTable::getHighScoreTable() {
    return highscores;
}

void HighScoreTable::updateTable(Score newScore) {

    for(auto& elem: highscores)
        if(newScore.id == elem.id) {
            elem.score = newScore.score;
            return;
        }

    if(highscores.size() > 12)
        highscores.clear();

    highscores.push_back(newScore);
}

bool cmp(const Score& sc1, const Score& sc2){
    return sc1.score > sc2.score;
}

void HighScoreTable::sort() {
    std::sort(highscores.begin(), highscores.end(), cmp);
}