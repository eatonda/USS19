

#ifndef GETHIGHSCORES_HPP
#define GETHIGHSCORES_HPP

#include <vector>
#include <string>

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

std::vector<std::vector<std::string> > getHighScores();

#endif
