#include <iostream>
#include <vector>
#include <time.h>
#include <string>
using namespace std;

#define ALPHABET_LENGTH 26

#define A 97
#define Z 122
#define END 123

/*
Algorithm to beat wordle

Dictionary of all words still possible

For 6 iterations:
	Pick one of two methods to take a guess

	1. Simple Likelihood (Minimum used once)
		Pick most likely word based off character frequency

	2. Elimination
		Pick a word with no known characters (00 or 11)
		This word should be the most likely out of all words of such a set
*/

vector<string> solveWordle(string correct_word, vector<string> dict) {

	

}

//Create every possible 5-character combination
vector<string> getDictionary() {
	vector<string> dict;
	//5 letter words
	//from a-z 1st, 2nd on each 1st, 3rd on each 2nd, etc.
	string n = "";
	for (int a = A; a < END; ++a) 
	for (int b = A; b < END; ++b) 
	for (int c = A; c < END; ++c)
	for (int d = A; d < END; ++d) 
	for (int e = A; e < END; ++e) {
		n = "" + a + b + c + d + e;
		dict.push_back(n);
	}

	return dict
}

//MAIN
int main(int argc, char *argv[]) {
	srand(time(0));
	vector<string> dict = getDictionary();
	string correct_word = dict[(int)(rand() * dict.size())];
	vector<string> solution = solveWordle(correct_word, dict);
}