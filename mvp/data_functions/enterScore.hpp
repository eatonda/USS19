
#ifndef ENTERSCORE_HPP
#define ENTERSCORE_HPP

#include <string>
#include "../../clunky_gl/clunkyCore.h"
#include "../../clunky_gl/clunkyHash.h"
#include "../../clunky_gl/clunkyEventElements.h"

// calculates and returns a player's score
int calcScore(int numRounds, int boardRows, int boardCols);

// returns true if a given score is a high score and false otherwise
bool isHighScore(int score);

// attempts to enter a score into the list of high scores, but only
// if it is a high score. Returns true if the score is a high score
// and was entered into the high score list and false otherwise
bool enterScore(int score, std::string playerName);

#endif
