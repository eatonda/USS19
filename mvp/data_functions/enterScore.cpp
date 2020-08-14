
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

// returns true if a given score is a high score and false otherwise
bool isHighScore(int score) {

	const int NUM_HIGH_SCORES = 10;

	// get the list of high scores
	std::vector<std::vector<std::string> > highScores = getHighScores();		

	// if there are less than 10 high scores, then this must be a high score
	if (highScores.size() < NUM_HIGH_SCORES) {
		return true;
	}
	// otherwise check to see if the score is larger than the smallest score
	return (score > std::stoi(highScores[highScores.size() - 1][1]));
}

// sorts the scores in descending order. The last score entered is at the
// the last index, and all other scores are already sorted in descending order 
void sortScores(std::vector<std::vector<std::string> > &highScores) {

	// find the first score less than the new score
	int curIndex = 0;
	int latestScore = std::stoi(highScores[highScores.size() - 1][1]);

	while (latestScore < std::stoi(highScores[curIndex][1])) {
		curIndex++;
	}

	int newScoreInd = curIndex;

	std::vector<std::string> newRow = highScores[highScores.size() - 1];

	std::vector<std::string> prevRow = highScores[curIndex];
	// move all of the other scores back 1 index
	while (curIndex < highScores.size() - 1) {
		std::vector<std::string> nextRow = highScores[curIndex + 1];
		highScores[curIndex + 1] = prevRow;
		prevRow = nextRow;
		curIndex++;
	}

	// enter in the new score at the proper location
	highScores[newScoreInd] = newRow;
}

// takes in a player's score and determines if it is a high
// score. If it is a high score, the score is entered into the 
// appropriate location in the scores file. If it is a high score
// this function returns true and returns false otherwise.
// PRECONDITIONS:
// 	- this function should only be called if the player won the game 
//	- the scores file is already sorted (this will be the case if all
//		scores were entered using this function

bool enterScore(int score, std::string playerName) {

	const int NUM_HIGH_SCORES = 10;

	if (isHighScore(score)) {
		// make the new row
		std::vector<std::string> scoreRow;
		scoreRow.push_back(playerName);
		scoreRow.push_back(std::to_string(score));		

		// get the list of high scores
		std::vector<std::vector<std::string> > highScores = getHighScores();		

		// if there are less than 10 scores, don't need to do anything before adding
		// the new score. But if there are 10 scores, remove the smallest
		if (highScores.size() == NUM_HIGH_SCORES) {		
			highScores.pop_back();	
		}		

		highScores.push_back(scoreRow);

		sortScores(highScores);

/*		// sort the modified scores vector in descending order
		std::sort(highScores.begin(), highScores.end(), [] 
			(const std::vector<std::string> &a, 
			const std::vector<std::string> &b) {
				return std::stoi(a[1]) > std::stoi(b[1]);
		});
*/

		// write the modified scores to the scores file
		writeScores(highScores);	

		return true;
	}

	// score was not a high score
	return false;	
}


