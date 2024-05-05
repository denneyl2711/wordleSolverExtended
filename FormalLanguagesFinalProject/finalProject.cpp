#include <iostream>
#include <fstream>
#include "Dawg.h"
using namespace std;
std::vector<std::string> readWordsFromFile(const std::string& filename);
int main() {

	//testing addChild
	/*DawgNode* nodeStart = new DawgNode;
	DawgNode* nodeC = nodeStart->addChild('c');
	DawgNode* nodeR = nodeC->addChild('r');
	DawgNode* nodeA = nodeR->addChild('a');
	DawgNode* nodeZ = nodeA->addChild('z');
	DawgNode* nodeE = nodeZ->addChild('e');*/
	//----------------------------------------------------------------------------------
	cout << "Runs at all" << endl;
	vector <string> words = { "cat", "fact", "facts", "facet", "facets"};
	//vector<string> words = { "truce", "spruce", "reduce" };
	//vector<string> words = readWordsFromFile("wordleWords.txt");

	/*for (string word : words) {
		cout << word << endl;
	}*/

	Dawg dawg1(words);
	cout << "constructed" << endl;

	//testing prefix-getting
	/*string pre = dawg1.findPrefixString("cats");
	cout << "Prefix is " << pre << endl;*/

	//testing printWords()
	DawgNode* root = dawg1.getRoot();
	dawg1.printWords();

	cout << "Root --->" <<  *root << endl;

	/*DawgNode* beginCat = root->getEdge('c')->getDestination();
	cout << "Node after root (cat path) is: " << *beginCat << endl;
	
	DawgNode* beginFacts = root->getEdge('f')->getDestination();
	cout << "Node after root (facts path) is: " << *beginFacts << endl;*/

	//dawg1.clear();
	dawg1.printWords();

	//Testing destructor
	/*cout << "Testing destructor ---------------------> (open task manager)" << endl;
	cout << "Creating and destroying many many dawgs (this will take several minutes to complete)" << endl;
	for (int i = 0; i < 100; ++i) {
		Dawg dawg2(words);
	}
	cout << "Done creating and deleting items" << endl;*/


	{
		cout << "Testing assignment operator." << endl;
		Dawg newDawg = dawg1;
		cout << "Printing words from newDawg" << endl;
		newDawg.printWords();
	}
	//dawg 1 should not be affected (should still print words)
	cout << "Printing words from original dawg after self assignment" << endl;
	dawg1 = dawg1;
	dawg1.printWords();



	cout << "Works now (by some miracleeee) (no linker errors now rn frfrfr)" << endl;


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