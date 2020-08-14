
#include <fstream>
#include <string>
#include <vector>

// returns a vector containing all of the high scores as player names 
// and the scores themselves. The data is organized in descending order 
// with the best score as the first element. For example, if the 
// vector returned by this function is copied and named scores, then 
// the name of the player with the top score can be accessed as (assuming 
// there is at least one high score):
//		scores[0][0]
// And the top score itself can be accessed as:
//		scores[0][1]
// Both the player name and the score are represented as strings.
// If there are no high scores in the high scores file, then this function
// returns an empty vector.
//
//	PRECONDITIONS:
//		- high scores are contained in the following relative path:
//			- "../data/high_scores/scores.txt"
//		- scores in that file are arranged in descending order (i.e. best
//		score comes first in the file)
//		- each line in the file starts with the player name then there is 
//		a single tab followed by the score for that player followed by a 
//		newline character.

std::vector<std::vector<std::string>> getHighScores() {

	// vector which will hold the player names and respective high scores
	std::vector<std::vector<std::string>> highScores;

	// string will hold lines from the scores file
	std::string line;

	// open the high scores file
	std::ifstream scoresFile("../data/high_scores/scores.txt");

	// if there is an error in opening the high scores file, then
	// the function will return an empty vector
	if (scoresFile.is_open()) {
		// read each line from the file
		while (std::getline(scoresFile, line)) {	
			std::string playerName = "";
			std::string score = "";
			int curPos = 0;

			// the first part of the line is the player name and a tab
			// separates it from the score
			while (line[curPos] != '\t') {
				playerName += line[curPos];
				curPos++;
			}

			curPos++;
			while (line[curPos] != '\0') {
				score += line[curPos];
				curPos++;
			}

			// add the player name and score as a row in the vector
			std::vector<std::string> newRow = { playerName, score };
			
			highScores.push_back(newRow);	
		}
	
		// all scores have been read, close the file
		scoresFile.close();
	}

	return highScores;	
}
