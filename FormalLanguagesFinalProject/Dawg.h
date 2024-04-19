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

	DawgNode(char letter) {
		letters.push_back(letter);
	}

	void addParent(DawgNode* node) {
		parents.push_back(node);
	}

	DawgNode* addChild(DawgNode* node) {
		children.push_back(node);
		node->addParent(this);
		return node;
	}


	DawgNode* addChild(char letter) {
		DawgNode* newNode = new DawgNode(letter);
		children.push_back(newNode);
		newNode->addParent(this);
		return newNode;
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
	friend std::ostream& operator<<(std::ostream& os, const DawgNode& obj) {
		os << "DawgNode value: ";
		for (int i = 0; i < obj.getLetters().size(); i++) {
			os << obj.getLetters().at(i);
		}

		return os;
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

	//void addWord(string word) {
	//}

	//if the user enters "cats" and "cat" is in the DAWG, then "cat" will be returned
	/*string findPrefix(string word) {

	}*/

};