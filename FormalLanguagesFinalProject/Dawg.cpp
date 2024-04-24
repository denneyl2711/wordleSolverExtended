#include "Dawg.h"

Edge::Edge(char letter, DawgNode* start, DawgNode* destination) {
    this->letter = letter;
    this->start = start;
    this->destination = destination;
}

Edge::Edge(DawgNode* parent, DawgNode* child) {
    this->letter = ' ';
    this->start = parent;
    this->destination = child;
}
//end Edge
//---------------------------------------------------------------------------------------------------
//begin DawgNode

DawgNode::DawgNode() {
    terminal = false;
}

void DawgNode::addParent(DawgNode* node) {
    Edge* edge = new Edge(' ', this, node);
    parents.push_back(edge);
}

DawgNode* DawgNode::addChild(char letter) {
    DawgNode* newNode = new DawgNode();
    Edge* edge = new Edge(letter, this, newNode);
    children.push_back(edge);
    newNode->addParent(this);
    return newNode;
}

set<DawgNode*> DawgNode::getChildrenNodes() const {
    set <DawgNode*> nodes;

    for (Edge* child : children) {
        nodes.insert(child->getDestination());
    }

    return nodes;
}

vector<DawgNode*> DawgNode::getParentNodes() const {
    set <DawgNode*> nodes;

    for (Edge* parent : parents) {
        nodes.insert(parent->getDestination());
    }

    vector <DawgNode*> vectorNodes(nodes.begin(), nodes.end());

    return vectorNodes;
}

bool DawgNode::hasEdge(char letter) {
    for (Edge* child : children) {
        if (child->getLetter() == letter) {
            return true;
        }
    }

    return false;
}

Edge* DawgNode::getEdge(char letter) {
    for (Edge* child : children) {
        if (child->getLetter() == letter) {
            return child;
        }

    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const DawgNode& obj) {
    os << "DawgNode value: ";
    auto children = obj.getChildEdges();
    for (int i = 0; i < children.size(); i++) {
        os << children.at(i)->getLetter();
    }

    return os;
}

//end DawgNode
//---------------------------------------------------------------------------------------------------
//begin Dawg

Dawg::Dawg(vector<string> wordList) {
    this->wordList = wordList;
    root = new DawgNode();
}

void Dawg::addWord(string word) {
    DawgNode* currentNode = findPrefixNode(word);
    int lengthPre = findPrefixString(word).length();
    for (int i = lengthPre; i < word.length(); i++) {
        currentNode = currentNode->addChild(word.at(i));
    }

    currentNode->setTerminal(true);
}

void Dawg::reduce() {
    // Not implemented yet
}

string Dawg::findPrefixString(string word) {
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

DawgNode* Dawg::findPrefixNode(string word) {
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

vector<string> Dawg::getWords()
{
    vector<string> words;

    //pass words by reference
    getWordsRec(root, "", words);

    return words;
}

void Dawg::printWords()
{
    vector<string> words = getWords();
    for (string word : words) {
        cout << word << endl;
    }
}

void Dawg::getWordsRec(DawgNode* node, string prefix, vector<string>& wordList) {
    if (node->getTerminal()) {
        wordList.push_back(prefix);
    }

    string oldPrefix = prefix;
    for (Edge* edge : node->getChildEdges()) {
        node = edge->getDestination();
        prefix += edge->getLetter();
        getWordsRec(node, prefix, wordList);
        prefix = oldPrefix;
    }
}
