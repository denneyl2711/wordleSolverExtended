#include <iostream>
#include "Dawg.h"
using namespace std;
int main() {
	DawgNode* nodeStart = new DawgNode;
	DawgNode* nodeC = nodeStart->addChild('c');
	DawgNode* nodeR = nodeC->addChild('r');
	DawgNode* nodeA = nodeR->addChild('a');
	DawgNode* nodeZ = nodeA->addChild('z');
	DawgNode* nodeE = nodeZ->addChild('e');

	vector <string> words = { "cat", "fact", "facts", "facet", "facets" };
	Dawg dawg1(words);
	dawg1.addWord("cat");
	//cout << "test" << endl;
	dawg1.addWord("facts");
	string pre = dawg1.findPrefixString("cats");
	/*cout << *nodeA << endl;
	cout << *(dawg1.findPrefixNode("facet")) << endl;
	cout << dawg1.getRoot()->hasEdge('a') << endl;
	cout << "Root "<< * (dawg1.getRoot()) << endl;

	cout << "Prefix " << pre << endl;


	cout << nodeZ->getNumChildren() << endl;*/

	dawg1.addWord("cats");
	dawg1.printWords(dawg1.getRoot(), "");
	cout << *(dawg1.getRoot()) << endl;
	cout << "End test" << endl;
	cout << "nothing changed" << endl;

	return 0;
}