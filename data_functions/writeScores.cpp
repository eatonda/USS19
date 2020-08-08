
#include <vector>
#include <string>
#include <fstream>

// uses the input vector to write in the high scores to the scores.txt file.
//
// PRECONDITIONS:
// 	- the rows in the scores vector have the first element as the player
//	name and the second element as the respective score
//	- the scores are sorted in descending order from best score to worst score
//	- the scores.txt file is in the following relative path:
//		"../data/high_scores/scores.txt"

void writeScores(std::vector<std::vector<std::string>> scores) {

	const std::string scoreFilePath = "../data/high_scores/scores.txt";

	std::ofstream scoresFile;

	// open the high scores file and allow overwriting
	scoresFile.open(scoreFilePath, std::ofstream::out | std::ofstream::trunc);

	// write in new scores	
	if (scoresFile.is_open()) {

		// write in each of the scores
		for (int i = 0; i < scores.size(); i++) {
			scoresFile << scores[i][0] << "\t" << scores[i][1] << "\n";
		}

		// close the file
		scoresFile.close();
	}
}
