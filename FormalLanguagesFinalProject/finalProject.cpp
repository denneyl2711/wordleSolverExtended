#include <iostream>
#include "Dawg.h"
using namespace std;
int main() {

	//testing addChild
	/*DawgNode* nodeStart = new DawgNode;
	DawgNode* nodeC = nodeStart->addChild('c');
	DawgNode* nodeR = nodeC->addChild('r');
	DawgNode* nodeA = nodeR->addChild('a');
	DawgNode* nodeZ = nodeA->addChild('z');
	DawgNode* nodeE = nodeZ->addChild('e');*/
	//----------------------------------------------------------------------------------

	vector <string> words = { "cat", "fact", "facts", "facet", "facets", "great", "janky", "welds"};
	Dawg dawg1(words);
	
	for (string word : words) {
		dawg1.addWord(word);
	}

	//testing prefix-getting
	/*string pre = dawg1.findPrefixString("cats");
	cout << "Prefix is " << pre << endl;*/

	//testing printWords()
	DawgNode* root = dawg1.getRoot();
	dawg1.printWords();

	cout << "Root --->" <<  * root << endl;

	DawgNode* beginCat = root->getEdge('c')->getDestination();
	cout << "Node after root (cat path) is: " << *beginCat << endl;
	
	DawgNode* beginFacts = root->getEdge('f')->getDestination();
	cout << "Node after root (facts path) is: " << *beginFacts << endl;

	cout << "Works now (by some miracleeee) (no linker errors now)" << endl;


	return 0;
}