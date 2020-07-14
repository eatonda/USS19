
#ifndef ENTERSCORE_HPP
#define ENTERSCORE_HPP

#include <string>

// calculates a player's score and determines if it is a high
// score. If it is a high score, the score is entered into the 
// appropriate location in the scores file. If it is a high score
// this function returns true and returns false otherwise.
// PRECONDITIONS:
// 	- this function should only be called if the player won the game 

bool enterScore(int numRounds, int boardRows, int boardCols,
	std::string playerName);

#endif
