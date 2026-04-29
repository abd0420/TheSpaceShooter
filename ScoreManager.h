#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H
#include <fstream>

class ScoreManager {
private:
    int score, highScore;
public:
    ScoreManager() : score(0) {
        std::ifstream f("highscore.txt");
        if (f >> highScore) f.close(); 
        else highScore = 0;
    }

    // Overloaded ++ operator to ease score addition
    ScoreManager& operator++() { 
        score += 10; 
        if (score > highScore) highScore = score; 
        return *this; 
    }

    void finalize() {
        std::ofstream f("highscore.txt");
        f << highScore;
        score = 0;
    }

    int getScore() const { return score; }
    int getHighScore() const { return highScore; }

    friend std::ostream& operator<<(std::ostream& os, const ScoreManager& sm);
};
inline std::ostream& operator<<(std::ostream& os, const ScoreManager& sm) {
    // for terminal testing
    os << "Current: " << sm.score << " | Best: " << sm.highScore;
    return os;
 }
#endif