#include <iostream>
#include <fstream>
#include "Trie.h"
using namespace std;
std::vector<std::string> readWordsFromFile(const std::string& filename);
void testDestructor(const vector<string>&);
int main() {
	
	//string source = "wordleWords.txt"; // ~2,000 words, list of possible accepting words (outdated, may miss a few words)

	string source = "wordleWordsFull.txt"; // ~15,000 words, every word accepted as a valid guess
	vector<string> words = readWordsFromFile(source);
	Trie wordleTrie(words);
	cout << "Words available: "<< wordleTrie.getWords().size() << endl;

	string userGuess;
	string guessInfo;

	//testDestructor(words);
	
	for (int i = 0; i < 6; ++i) {
		cout << endl;

		cout << "Enter guess #" << i + 1 << ": ";
		cin >> userGuess;

		cout << "Enter guess information in form green=Y, yellow=M, grey=N" << endl;
		cin >> guessInfo;

		//check for bad user input
		//can add more conditions later
		bool badGuess = false;

		if (userGuess.length() != guessInfo.length()) {
			cout << "Word length doesn't match guess info length. Please try again." << endl;
			badGuess = true;
		}

		for (char letter : guessInfo) {
			if (toupper(letter) != 'Y' &&
				toupper(letter) != 'M' &&
				toupper(letter) != 'N') {
				cout << "Guess info is invalid. Please try again. " << endl;
				badGuess = true;
				break;
			}

		}

		if (badGuess) { i--;  continue; }

		wordleTrie.prune(guessInfo, userGuess);
		cout << "Possible solutions: " << endl;
		wordleTrie.printWords();
		cout << "Words available: " << wordleTrie.getWords().size() << endl;
	}


	return 0;
}

std::vector<std::string> readWordsFromFile(const std::string& filename) {
	std::vector<std::string> words;
	std::ifstream file(filename);
	std::string word;

	if (file.is_open()) {
		while (file >> word) {
			words.push_back(word);
		}
		file.close();
	}
	else {
		std::cerr << "Unable to open file " << filename << std::endl;
	}

	return words;
}

void testDestructor(const vector<string>& words) {
	for (int i = 0; i < 15000; ++i) {
		Trie trie(words);
	}
}
