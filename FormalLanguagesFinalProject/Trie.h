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

	//void redirect(DawgNode* node);

	void setTerminal(bool terminal) { this->terminal = terminal; }

	void addParent(DawgNode* node);

	DawgNode* addChild(char letter);

	int getNumParents() { return parents.size(); }

	int getNumChildren() { return children.size(); }

	vector<Edge*> getChildEdges() const { return children; }

	vector<Edge*> getChildEdges() { return children; }

	set<DawgNode*> getChildrenNodes() const;

	vector<Edge*> getParentsEdges() const { return parents; }

	vector<DawgNode*> getParentNodes() const;

	void removeChildEdge(Edge* edge);

	void removeParentEdge(Edge* edge);

	bool hasEdge(char letter);

	Edge* getEdge(char letter);


	friend std::ostream& operator<<(std::ostream& os, const DawgNode& obj);
};

class Trie {
private:
	DawgNode* root;
	//DawgNode* lastAdded;

	void getWordsRec(DawgNode* node, string prefix, vector<string>& wordList) const;

	//void reduce(DawgNode* current);

	//delete the passed-in node and proceeding nodes
	void eraseNode(DawgNode*);

public:
	Trie(vector<string> wordList);

	~Trie() { cout << endl << endl << "Destroying dawg " << endl; eraseNode(root); }

	Trie(const Trie& dawg);

	Trie& operator= (const Trie& other);

	DawgNode* getRoot() { return root; }

	void addWord(string word);

	void addWords(vector<string> words);

	DawgNode* clear(); //remove all nodes and return a pointer to the new root

	string findPrefixString(string word);

	DawgNode* findPrefixNode(string word);

	vector<string> getWords() const;

	void printWords() const;

	void prune(string guessInfo, string guess);

	void pruneGreen(char letter, int idx);

	void pruneGreenRec(char letter,int currentIdx, int targetIdx, DawgNode* node);

	void pruneYellow(char letter, int idx);

	void pruneYellowRec(char letter, int currentIdx, int targetIdx, DawgNode* node);

	void pruneByIdx(char letter, int idx);

	void pruneByIdxRec(char letter, int currentIdx, int targetIdx, DawgNode* node);

	void pruneGrey(char letter);

	void pruneGreyRec(char letter, DawgNode* node);


};

#endif // DAWG_H
