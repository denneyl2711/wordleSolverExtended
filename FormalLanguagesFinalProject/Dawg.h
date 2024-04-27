#ifndef DAWG_H
#define DAWG_H

#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

class DawgNode;

class Edge {
private:
	char letter;
	DawgNode* start;
	DawgNode* destination;
public:
	Edge(char letter, DawgNode* start, DawgNode* destination);

	Edge(DawgNode* parent, DawgNode* child);
	
	void setDestination(DawgNode* node) { this->destination = node; }

	void setStart(DawgNode* node) { this->start = node; }

	char getLetter() { return letter; }

	DawgNode* getDestination() { return destination; }
};

class DawgNode {
private:
	vector<Edge*> parents;
	vector<Edge*> children;
	bool terminal;

public:
	DawgNode();

	bool getTerminal() { return terminal; }

	void setTerminal(bool terminal) { this->terminal = terminal; }

	void addParent(DawgNode* node);

	DawgNode* addChild(char letter);

	int getNumParents() { return parents.size(); }

	int getNumChildren() { return children.size(); }

	vector<Edge*> getChildEdges() const { return children; }

	set<DawgNode*> getChildrenNodes() const;

	vector<Edge*> getParentsEdges() const { return parents; }

	vector<DawgNode*> getParentNodes() const;

	bool hasEdge(char letter);

	Edge* getEdge(char letter);


	friend std::ostream& operator<<(std::ostream& os, const DawgNode& obj);
};

class Dawg {
private:
	DawgNode* root;
	DawgNode* lastAdded;

	void getWordsRec(DawgNode* node, string prefix, vector<string>& wordList) const;

public:
	Dawg(vector<string> wordList);

	~Dawg() { eraseNode(root); if (lastAdded != nullptr){delete lastAdded; } }

	Dawg(const Dawg& dawg);

	Dawg& operator= (const Dawg& other);

	DawgNode* getRoot() { return root; }

	void addWord(string word);

	void addWords(vector<string> words);

	void reduce(DawgNode* current);

	string findPrefixString(string word);

	DawgNode* findPrefixNode(string word);

	vector<string> getWords() const;

	void printWords() const;

	//delete the passed-in node and proceeding nodes
	void eraseNode(DawgNode*);
};

#endif // DAWG_H
