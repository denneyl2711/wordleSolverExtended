#ifndef DAWG_H
#define DAWG_H

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;

class TrieNode;

class Edge {
private:
	char letter;
	TrieNode* start;
	TrieNode* destination;
public:
	Edge(char letter, TrieNode* start, TrieNode* destination);

	Edge(TrieNode* parent, TrieNode* child);
	
	void setDestination(TrieNode* node) { this->destination = node; }

	void setStart(TrieNode* node) { this->start = node; }

	char getLetter() { return letter; }

	TrieNode* getDestination() { return destination; }
};

class TrieNode {
private:
	vector<Edge*> parents;
	vector<Edge*> children;
	bool terminal;

public:
	TrieNode();

	bool getTerminal() { return terminal; }

	//void redirect(TrieNode* node);

	void setTerminal(bool terminal) { this->terminal = terminal; }

	void addParent(TrieNode* node);

	bool parentBranchContainsLetter(char letter);

	TrieNode* addChild(char letter);

	int getNumParents() { return parents.size(); }

	int getNumChildren() { return children.size(); }

	vector<Edge*> getChildEdges() const { return children; }

	vector<Edge*> getChildEdges() { return children; }

	set<TrieNode*> getChildrenNodes() const;

	vector<Edge*> getParentsEdges() const { return parents; }

	vector<TrieNode*> getParentNodes() const;

	void removeChildEdge(Edge* edge);

	void removeParentEdge(Edge* edge);

	bool hasEdge(char letter);

	Edge* getEdge(char letter);


	friend std::ostream& operator<<(std::ostream& os, const TrieNode& obj);
};

class Trie {
private:
	TrieNode* root;
	//TrieNode* lastAdded;

	void getWordsRec(TrieNode* node, string prefix, vector<string>& wordList) const;

	//void reduce(TrieNode* current);

	//delete the passed-in node and proceeding nodes
	void eraseNode(TrieNode*);

	static unordered_map<char, vector<int>> findDuplicates(const string& str);

	void pruneGreenRec(char letter, int currentIdx, int targetIdx, TrieNode* node);
	void pruneYellowRec(char letter, int currentIdx, int targetIdx, TrieNode* node);
	void pruneGreyRec(char letter, TrieNode* node);

public:
	Trie(vector<string> wordList);

	~Trie() { cout << endl << endl << "Destroying dawg " << endl; eraseNode(root); }

	Trie(const Trie& dawg);

	Trie& operator= (const Trie& other);

	TrieNode* getRoot() { return root; }

	void addWord(string word);

	void addWords(vector<string> words);

	TrieNode* clear(); //remove all nodes and return a pointer to the new root

	string findPrefixString(string word);

	TrieNode* findPrefixNode(string word);

	vector<string> getWords() const;

	void printWords() const;

	void prune(string guessInfo, string guess);

	void pruneGreen(char letter, int idx);

	void pruneYellow(char letter, int idx);

	void pruneByIdx(char letter, int idx);

	void pruneByIdxRec(char letter, int currentIdx, int targetIdx, TrieNode* node);

	void pruneGrey(char letter);

};

#endif // DAWG_H
