
#include <string>
#include <vector>
#include <algorithm>
#include "getHighScores.hpp"
#include "writeScores.hpp"

// calculates a score based on the number of rounds used to win
// and the size of the board. A lower number of rounds will have a 
// positive impact on the score and smaller board will have a negative 
// impact on the score (relative to the number of rounds played).
int calcScore (int numRounds, int boardRows, int boardCols) {

	// include a multiplier for more diverse scores
	const int squaresMultiplier = 10;

	// calculate number of squares on board
	int numSquares = boardRows * boardCols;

	// calculate and return the score
	return ((numSquares * squaresMultiplier) / numRounds);
}


// calculates a player's score and determines if it is a high
// score. If it is a high score, the score is entered into the 
// appropriate location in the scores file. If it is a high score
// this function returns true and returns false otherwise.
// PRECONDITIONS:
// 	- this function should only be called if the player won the game 
//	- the scores file is already sorted (this will be the case if all
//		scores were entered using this function

bool enterScore(int numRounds, int boardRows, int boardCols,
	std::string playerName) {

	const int NUM_HIGH_SCORES = 10;

	// calculate the player's score
	int score = calcScore(numRounds, boardRows, boardCols);

	// get the list of current high scores
	std::vector<std::vector<std::string>> highScores = getHighScores();

	// will hold true if the score is added to the high scores
	bool scoreAdded = false;

	std::vector<std::string> scoreRow = { playerName, std::to_string(score) };
	// see if this is a high score, and if so add it to the vector
	if (highScores.size() < 10) {	
		highScores.push_back(scoreRow);	
		scoreAdded = true;
	}	
	else if (score > std::stoi(highScores[highScores.size() - 1][1])) {
		highScores.pop_back();
		highScores.push_back(scoreRow);
		scoreAdded = true;
	}

	if (scoreAdded) {

		// sort the new scores vector in descending order
		std::sort(highScores.begin(), highScores.end(), [] 
			(const std::vector<std::string> &a, 
			const std::vector<std::string> &b) {
				return std::stoi(a[1]) > std::stoi(b[1]);
		});

		// write the sorted vector to the scores file
		writeScores(highScores);	
	}

	return scoreAdded;
}


