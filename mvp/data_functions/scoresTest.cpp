
#include "getHighScores.hpp"
#include "writeScores.hpp"
#include "enterScore.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <cassert>

// test file to check that the writeScores and the getHighScores functions 
// are working properly

int main() {

	// test scores to write to the scores file	
	std::vector<std::vector<std::string>> testScores {
		{ "doug", "20" },
		{ "sheep", "15" },
		{ "cow", "12" }
	};

	// write the scores to the file
	writeScores(testScores);	

	// retrieve the high scores from the file
	std::vector<std::vector<std::string>> scores = getHighScores();	

	// verify that scores written to the file match the scores
	// retrieved by getHighScores
	assert(testScores.size() == scores.size() &&
		"The number of scores written does not match the number of scores retrieved.");

	std::cout << "TEST 1 PASSED: the number of scores written equals the "
		<< "number of scores retrieved.\n";

	for (int i = 0; i < testScores.size(); i++) {
		assert(testScores[i][0] == scores[i][0] &&
			"A player name does not match.");
		assert(testScores[i][1] == scores[i][1] &&
			"A score does not match.");
	}

	std::cout << "TEST 2 PASSED: all scores written and retrieved match.\n";

	// new test scores to write to the scores file
	std::vector<std::vector<std::string>> testScores2 {
		{ "bill", "27" },
		{ "asdf", "25" },
		{ "jack", "24" },
		{ "cow", "24" },
		{ "EMily", "22" },
		{ "player624", "18" },
		{ "0rangE", "17" },
		{ "NAte43", "14" },
		{ "sharkGirl", "13"},
		{ "f43qf", "10" }
	};	

	// write the new scores to the file
	writeScores(testScores2);

	// retrieve the new scores from the file
	scores = getHighScores();

	// verify that scores written to the file match the scores
	// retrieved by getHighScores
	assert(testScores2.size() == scores.size() &&
		"The number of scores written does not match the number of scores retrieved.");

	std::cout << "TEST 3 PASSED: the number of scores written equals the "
		<< "number of scores retrieved.\n";

	for (int i = 0; i < testScores2.size(); i++) {
		assert(testScores2[i][0] == scores[i][0] &&
			"A player name does not match.");
		assert(testScores2[i][1] == scores[i][1] &&
			"A score does not match.");
	}

	std::cout << "TEST 4 PASSED: all scores written and retrieved match.\n";

	// enter a new score
	enterScore(54, 10, 10, "aaaaa");
	
	return 0;
}
