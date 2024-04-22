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
	Edge(char letter, DawgNode* parent, DawgNode* child) {
		this->letter = letter;
		this->start = parent;
		this->destination = child;
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

public:
	DawgNode() {
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