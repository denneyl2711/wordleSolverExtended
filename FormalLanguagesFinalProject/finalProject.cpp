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

	cout << nodeZ->getNumChildren() << endl;

	return 0;
}