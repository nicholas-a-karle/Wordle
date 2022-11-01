#include <iostream>
#include <vector>
#include <time.h>
#include <string>
using namespace std;

#define ALPHABET_LENGTH 26

#define WORD_LENGTH 5
#define A 97
#define Z 122
#define END 123
#define MAX_GUESSES 6

/*
Algorithm A for wordle
	Record of which letters are possible in each space
	Create words from picking these letters at random
	Note: No intelligence really, not guessing most common letters, etc.
*/
int algoA(string correct_word) {
	
	vector<vector<char>> letters;
	for (int i = 0; i < WORD_LENGTH; ++i) {
		vector<char> v;
		for (int c = A; c <=Z; ++c) {
			v.push_back((char)c);
		}
		letters.push_back(v);
	}

	int num_iter = 0;

	string guess_word = "*****";

	while (guess_word != correct_word) {

		//create guess word
		guess_word = "";
		for (int i = 0; i < WORD_LENGTH; ++i) {
			guess_word += letters[i][rand() % letters[i].size()];
		}

		//cout << "Guess Word:\t" << guess_word << endl;
		//cout << "Result:\t\t";

		//get results of guess word
		//also limit the letters
		for (int i = 0; i < WORD_LENGTH; ++i) {
			char g = guess_word[i];
			bool in_word = false;
			bool in_spot = false;
			for (int k = 0; k < WORD_LENGTH; ++k) {
				char c = correct_word[k];
				if (g == c) {
					in_word = true;
					if (i == k) {
						in_spot = true;
						break;
					}
				}
			}

			//remove from lists
			if (in_spot && in_word) { //green
				//cout << "G";
				//set i to g
				letters[i] = {g};
			} else if (!in_spot && in_word) { //yellow
				//cout << "Y";
				//remove g from i
				for (auto it = letters[i].begin(); it < letters[i].end() ; ++it) {
					if (*it == g) letters[i].erase(it);
				}
			} else if (!in_word && !in_spot) {
				//cout << "R";
				//remove g from all
				for (int k = 0; k < WORD_LENGTH; ++k) {
					for (auto it = letters[k].begin(); it < letters[k].end() ; ++it) {
						if (*it == g) letters[k].erase(it);
					}
				}
			} else if (in_spot && !in_word) { //impossible
				//error
			}
		}
		
		//cout << endl;	

		//iterate
		++num_iter;
	}

	return num_iter;
}

/*
Algo B for Wordle
	Try to eliminate as many characters as possible, do not repeat in same word if not trying to guess
	Possibilities = 26 * 26 * 26 * 26 * 26 = [0][1][2][3][4]
		Reds reduce all by 1, Yellows reduce 1 by 1, Greens reduce 1 to 1
	Once possibilities are below a certain threshhold, start guessing
*/
int algoB(string correct_word, int possibility_threshold) {
	
	vector<vector<char>> possible_letters;
	for (int i = 0; i < WORD_LENGTH; ++i) {
		vector<char> v;
		for (int c = A; c <=Z; ++c) {
			v.push_back((char)c);
		}
		possible_letters.push_back(v);
	}
	vector<vector<char>> uncertain_letters = possible_letters;

	int num_iter = 0;

	string guess_word = "*****";

	while (guess_word != correct_word) {

		//decide whether to guess or eliminate
		int possibilities = 1;
		for (int i = 0; i < WORD_LENGTH; ++i) possibilities *= possible_letters[i].size();
		bool guess = possibilities < possibility_threshold;
		//cout << "" << possible_letters[0].size() << "\t"  << possible_letters[1].size() << "\t" 
		// 	<< possible_letters[2].size() << "\t"  << possible_letters[3].size() << "\t"  << possible_letters[4].size() << "\t"
		// 	<< possibilities << "\t";

		//create guess word
		guess_word = "";
		if (guess) {
			for (int i = 0; i < WORD_LENGTH; ++i) {
				guess_word += possible_letters[i][rand() % possible_letters[i].size()];
			}
		} else { //eliminate
			for (int i = 0; i < WORD_LENGTH; ++i) {
				if (uncertain_letters[i].size() > 0)
					guess_word += uncertain_letters[i][rand() % uncertain_letters[i].size()];
				else 
					guess_word += possible_letters[i][rand() % possible_letters[i].size()];
			}
		}


		//cout << "Guess Word:\t" << guess_word << endl;
		//cout << "Result:\t\t";

		//get results of guess word
		//also limit the possible_letters
		for (int i = 0; i < WORD_LENGTH; ++i) {
			char g = guess_word[i];
			bool in_word = false;
			bool in_spot = false;
			for (int k = 0; k < WORD_LENGTH; ++k) {
				char c = correct_word[k];
				if (g == c) {
					in_word = true;
					if (i == k) {
						in_spot = true;
						break;
					}
				}
			}

			//remove from lists
			if (in_spot && in_word) { //green
				//cout << "G";
				//set i to g
				possible_letters[i] = {g};
				//remove from uncertain
				for (int k = 0; k < WORD_LENGTH; ++k) {
					for (auto it = uncertain_letters[k].begin(); it < uncertain_letters[k].end() ; ++it) {
						if (*it == g) uncertain_letters[k].erase(it);
					}
				}
			} else if (!in_spot && in_word) { //yellow
				//cout << "Y";
				//remove g from i in all
				for (auto it = possible_letters[i].begin(); it < possible_letters[i].end() ; ++it) {
					if (*it == g) possible_letters[i].erase(it);
				}
				for (auto it = uncertain_letters[i].begin(); it < uncertain_letters[i].end() ; ++it) {
					if (*it == g) uncertain_letters[i].erase(it);
				}
			} else if (!in_word && !in_spot) { // red
				//cout << "R";
				//remove g from all
				for (int k = 0; k < WORD_LENGTH; ++k) {
					for (auto it = possible_letters[k].begin(); it < possible_letters[k].end() ; ++it) {
						if (*it == g) possible_letters[k].erase(it);
					}
					for (auto it = uncertain_letters[k].begin(); it < uncertain_letters[k].end() ; ++it) {
						if (*it == g) uncertain_letters[k].erase(it);
					}
				}
			} else { //impossible
				//error
				//cout << "___ERROR___";
			}
		}
		
		//cout << ((possibilities < possibility_threshold) ? ("\t\tGUESS") : ("\t\tELIMINATION")) << endl;	

		//iterate
		++num_iter;
	}

	return num_iter;
}

int algoC()

#define ITER 250000.0

//MAIN
int main(int argc, char *argv[]) {
	srand(time(0));
	vector<double> averages(14,0);
	string test_word = "reads";
	for (int i = 0; i < ITER; ++i) {
		averages[0] +=  algoB(test_word, 64*64*64*64) / ITER;
		averages[1] +=  algoB(test_word, 64*64*64) / ITER;
		averages[2] +=  algoB(test_word, 64*64) / ITER;
		averages[3] +=  algoB(test_word, 64) / ITER;
		averages[4] +=  algoA(test_word) / ITER;

		cout << "Progress: " << (i / ITER) << endl;
	}

	cout << "Algo1:\t\t"     << averages[0] << endl;
	cout << "Algo2:\t\t"     << averages[1] << endl;
	cout << "Algo3:\t\t"     << averages[2] << endl;
	cout << "Algo4:\t\t"     << averages[3] << endl;
	cout << "Algo5:\t\t"     << averages[4] << endl;
}