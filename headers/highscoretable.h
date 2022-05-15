#ifndef MAIN_CPP_HIGHSCORETABLE_H
#define MAIN_CPP_HIGHSCORETABLE_H

#include <utility>
#include <vector>
#include <string>

struct Score{
    int id, score;
    std::string name;

    Score(int ID, std::string Name, int Score){
        id = ID;
        name = Name;
        score = Score;
    }
};

class HighScoreTable{

private:
    std::vector<Score> highscores;

public:
    HighScoreTable();

    std::vector<Score> getHighScoreTable();

    void updateTable(Score newScore);

    void sort();

};

#endif //MAIN_CPP_HIGHSCORETABLE_H
