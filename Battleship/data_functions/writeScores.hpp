
#ifndef WRITESCORES_HPP
#define WRITESCORES_HPP

#include <vector>
#include <string>
#include "../../clunky_gl/clunkyCore.h"
#include "../../clunky_gl/clunkyHash.h"
#include "../../clunky_gl/clunkyEventElements.h"

// uses the input vector to write in the high scores to the scores.txt file.
//
// PRECONDITIONS:
// 	- the rows in the scores vector have the first element as the player
//	name and the second element as the respective score
//	- the scores are sorted in descending order from best score to worst score
//	- the scores.txt file is in the following relative path:
//		"../data/high_scores/scores.txt"

void writeScores(std::vector<std::vector<std::string> > scores);

#endif
