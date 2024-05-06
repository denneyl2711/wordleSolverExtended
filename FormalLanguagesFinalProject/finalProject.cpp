#include <iostream>
#include <fstream>
#include "Trie.h"
using namespace std;
std::vector<std::string> readWordsFromFile(const std::string& filename);
int main() {
	//testing functionality of trie
	////testing addChild
	///*TrieNode* nodeStart = new TrieNode;
	//TrieNode* nodeC = nodeStart->addChild('c');
	//TrieNode* nodeR = nodeC->addChild('r');
	//TrieNode* nodeA = nodeR->addChild('a');
	//TrieNode* nodeZ = nodeA->addChild('z');
	//TrieNode* nodeE = nodeZ->addChild('e');*/
	////----------------------------------------------------------------------------------
	//cout << "Runs at all" << endl;
	//vector <string> words = { "cat", "fact", "facts", "facet", "facets"};
	////vector<string> words = { "truce", "spruce", "reduce" };
	////vector<string> words = readWordsFromFile("wordleWords.txt");

	///*for (string word : words) {
	//	cout << word << endl;
	//}*/

	//Trie dawg1(words);
	//cout << "constructed" << endl;

	////testing prefix-getting
	///*string pre = dawg1.findPrefixString("cats");
	//cout << "Prefix is " << pre << endl;*/

	////testing printWords()
	//TrieNode* root = dawg1.getRoot();
	//dawg1.printWords();

	//cout << "Root --->" <<  *root << endl;

	///*TrieNode* beginCat = root->getEdge('c')->getDestination();
	//cout << "Node after root (cat path) is: " << *beginCat << endl;
	//
	//TrieNode* beginFacts = root->getEdge('f')->getDestination();
	//cout << "Node after root (facts path) is: " << *beginFacts << endl;*/

	////dawg1.clear();
	//dawg1.printWords();

	////Testing destructor
	///*cout << "Testing destructor ---------------------> (open task manager)" << endl;
	//cout << "Creating and destroying many many dawgs (this will take several minutes to complete)" << endl;
	//for (int i = 0; i < 100; ++i) {
	//	Trie dawg2(words);
	//}
	//cout << "Done creating and deleting items" << endl;*/


	//{
	//	cout << "Testing assignment operator." << endl;
	//	Trie newDawg = dawg1;
	//	cout << "Printing words from newDawg" << endl;
	//	newDawg.printWords();
	//}
	////dawg 1 should not be affected (should still print words)
	//cout << "Printing words from original dawg after self assignment" << endl;
	//dawg1 = dawg1;
	//dawg1.printWords();



	//cout << "Works now (by some miracleeee) (no linker errors now rn frfrfr)" << endl;


	//Wordle 
	vector<string> words = readWordsFromFile("wordleWords.txt");
	//vector<string> words = { "facet", "smile", "bored", "bores" };
	Trie wordleDawg(words);
	cout << "Words available: "<< wordleDawg.getWords().size() << endl;

	string userGuess;
	string guessInfo;
	
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

		wordleDawg.prune(guessInfo, userGuess);
		wordleDawg.printWords();
		cout << "Words available: " << wordleDawg.getWords().size() << endl;
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