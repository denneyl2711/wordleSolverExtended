#include <iostream>
#include <vector>
#include <string>
#include<set>
using namespace std;
class DawgNode;

class Edge {
private: 
	char letter;
	DawgNode* start;
	DawgNode* destination;
public:
	Edge(char letter, DawgNode* start, DawgNode* destination) {
		this->letter = letter;
		this->start = start;
		this->destination = destination;
	}

	Edge(DawgNode* parent, DawgNode* child) {
		this->letter = ' ';
		this->start = parent;
		this->destination = child;
	}

	char getLetter() {
		return letter;
	}

	/*DawgNode* getStart() {
		return start;
	}*/

	DawgNode* getDestination() {
		return destination;
	}


};


class DawgNode {
private:
	vector<Edge*> parents;
	vector<Edge*> children;
	bool terminal;

public:
	DawgNode() {
		terminal = false;
	}

	bool getTerminal() {
		return terminal;
	}

	void setTerminal(bool terminal) {
		this->terminal = terminal;
	}


	void addParent(DawgNode* node) {
		Edge* edge = new Edge(' ', this, node);
		parents.push_back(edge);
	}

	/*DawgNode* addChild(DawgNode* node) {
		Edge* edge = new Edge(' ', this, node);
		
		children.push_back(node);
		node->addParent(this);
		return node;
	}*/


	DawgNode* addChild(char letter) {
		DawgNode* newNode = new DawgNode();
		Edge* edge = new Edge(letter, this, newNode);
		children.push_back(edge);
		newNode->addParent(this);
		return newNode;
	}

	int getNumParents() {
		return parents.size();
	}

	int getNumChildren() {
		return children.size();
	}

	//vector of edges
	vector<Edge*> getChildEdges() const {
		return children;
	}

	//set of dawg nodes
	set<DawgNode*> getChildrenNodes() const {
		set <DawgNode*> nodes;

		for (Edge* child : children) {
			nodes.insert(child->getDestination());
		}

		return nodes;
	}


	vector<Edge*> getParentsEdges() const {
		return parents;
	}

	//set of dawg nodes
	vector<DawgNode*> getParentNodes() const {
		set <DawgNode*> nodes;

		for (Edge* parent : parents) {
			nodes.insert(parent->getDestination());
		}

		vector <DawgNode*> vectorNodes(nodes.begin(), nodes.end());
		

		return vectorNodes;
	}


	bool hasEdge(char letter) {
		for (Edge* child : children) {
			if (child->getLetter() == letter) {
				return true;
			}
			
		}

		return false;
	}

	Edge* getEdge(char letter) {
		for (Edge* child : children) {
			if (child->getLetter() == letter) {
				return child;
			}

		}
		return nullptr;
	}

	friend std::ostream& operator<<(std::ostream& os, const DawgNode& obj) {
		os << "DawgNode value: ";
		auto children = obj.getChildEdges();
		for (int i = 0; i < children.size(); i++) {
			os << children.at(i)->getLetter();
		}

		return os;
	}

};


class Dawg {
private:
	DawgNode* root;
	vector<string> wordList;
public:
	Dawg(vector<string> wordList) {
		this->wordList = wordList;
		root = new DawgNode();
	}


	DawgNode* getRoot() {
		return root;
	}

	//first implementation just adds all words to seperate branches (bad)
	void addWord(string word) {
		DawgNode* currentNode = findPrefixNode(word);
		int lengthPre = findPrefixString(word).length();
		//adds word to graph as seperate leaf
		for (int i = lengthPre; i < word.length(); i++) {
			currentNode = currentNode->addChild(word.at(i));
		}

		currentNode->setTerminal(true);

	}

	//simplify the DAWG
	void reduce() {
	}

	//void addWord(string word) {
	//}

	//if the user enters "cats" and "cat" is in the DAWG, then "cat" will be returned
	string findPrefixString(string word) {
		DawgNode* currentNode = root;
		string pre = "";
		for (int i = 0; i < word.length(); i++) {
			Edge* edge = currentNode->getEdge(word.at(i));
			if (edge == nullptr) {
				break;
			}
			else {
				pre += word.at(i);
				currentNode = edge->getDestination();
			}
		}
		return pre;
	}

	DawgNode* findPrefixNode(string word) {
		DawgNode* currentNode = root;
		for (int i = 0; i < word.length(); i++) {
			Edge* edge = currentNode->getEdge(word.at(i));
			if (edge == nullptr) {
				break;
			}
			else {
				currentNode = edge->getDestination();
			}
		}
		return currentNode;
	}

	void printWords(DawgNode* node, string prefix) {
		if (node->getTerminal()) {
			cout << prefix << endl;
			if (node->getNumChildren() == 0) {
				prefix = "";
			}
		}
		if (node == root) {
			prefix = "";
		}
		for (Edge* edge : node->getChildEdges()) {
				node = edge->getDestination();
				prefix = prefix + edge->getLetter();
				printWords(node, prefix);
				
		}
		
	}

};