#include<iostream>
#include<vector>
using namespace std;

class DawgNode {
private:
	vector<DawgNode*> parents;
	vector<DawgNode*> children;

public:
	DawgNode() {

	}

	void addParent(DawgNode* node) {
		parents.push_back(node);
	}

	void addChild(DawgNode* node) {
		children.push_back(node);
	}
};