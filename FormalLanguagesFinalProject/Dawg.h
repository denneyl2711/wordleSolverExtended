#include <iostream>
#include <vector>
#include <string>
using namespace std;

class DawgNode {
private:
	vector<DawgNode*> parents;
	vector<char> letters;
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

	int getNumParents() {
		return parents.size();
	}

	int getNumChildren() {
		return children.size();
	}

	vector<DawgNode*> getChildren() const {
		return children;
	}

	vector<DawgNode*> getParents() const {
		return parents;
	}

	vector<char> getLetters()const {
		return letters;
	}

	bool hasChild(char letter) {
		for (DawgNode* child : children) {
			for (char childLetter : child->getLetters()) {
				if (childLetter == letter) {
					return true;
				}
			}
		}

		return false;
	}

};

class Dawg {
private:
	DawgNode* root;
	vector<string> alphabet;

	Dawg(vector<string> alphabet) {
		this->alphabet = alphabet;
		root = new DawgNode();
	}

	void addWord(string word);

	//simplify the DAWG
	void reduce();

	void addWord(string word) {
	}

	//if the user enters "cats" and "cat" is in the DAWG, then "cat" will be returned
	string findPrefix(string word) {

	}

};