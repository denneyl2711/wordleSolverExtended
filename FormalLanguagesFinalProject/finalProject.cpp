#include <iostream>
#include "Dawg.h"
using namespace std;
int main() {
	DawgNode node;


	DawgNode* childNode = node.addChild('k');
	DawgNode* nodeTest = node.getChildren().at(0);
	cout << *nodeTest << endl;
	cout << *(childNode->getParents().at(0)) << endl;
	cout << node.getNumChildren() << endl;
	cout << childNode->getNumParents() << endl;

	return 0;
}