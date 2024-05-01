#include "Dawg.h"
#include <algorithm>

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


void DawgNode::redirect(DawgNode* node)
{
    Edge* edgeReverse = new Edge(' ', node, this);
    node->parents.push_back(edgeReverse);

    Edge* edge = new Edge(' ', this, node);
    this->children.push_back(edge);
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
    lastAdded = nullptr;
    addWords(wordList);
}

Dawg::Dawg(const Dawg& dawg)
{
    lastAdded = nullptr;
    this->addWords(dawg.getWords());
}

Dawg& Dawg::operator=(const Dawg& other)
{
    if (this != &other) {
        this->clear();
        this->addWords(other.getWords());
    }

    return *this;
}

//words are passed in, in reverse alphabetical order for this method
void Dawg::addWord(string word) {
    if (root == nullptr) {
        root = new DawgNode();
    }

    DawgNode* currentNode = findPrefixNode(word);
    int lengthPre = findPrefixString(word).length();
    for (int i = lengthPre; i < word.length(); i++) {
        currentNode = currentNode->addChild(word.at(i));
        lastAdded = currentNode;
    }
    currentNode->setTerminal(true);
    
    //reduce(currentNode);
}


void Dawg::addWords(vector<string> words)
{
    //sort words in reverse order before adding them
    //this ensures greater efficiency when adding nodes
    std::sort(words.begin(), words.end(), std::greater<>());

    for (string word : words) {
        addWord(word);
    }
}

void Dawg::reduce(DawgNode* current) {
    // Not implemented yet
    if (lastAdded == nullptr) {
        return;
    }
    vector <string> lastAddedRight;
    vector <string> currentRight;
    this->getWordsRec(lastAdded, "", lastAddedRight);
    this->getWordsRec(current, "", currentRight);

    if (lastAddedRight == currentRight) {
        //edge to be repointed 
        /*Edge* edge = current->getParentsEdges().at(0);
        edge->setDestination(lastAdded);
        lastAdded->addParent(current);*/
        DawgNode* node = current->getParentNodes().back();
        //delete old edge
        delete node->getChildEdges().back(); 
        //redirect edge
        node->redirect(lastAdded);
         //delete old node
        eraseNode(current);
    }

    //set last Added
}

DawgNode* Dawg::clear()
{
    eraseNode(root);
    root = new DawgNode();
    lastAdded = nullptr;
    return root;
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

vector<string> Dawg::getWords() const
{
    vector<string> words;

    //pass words by reference
    getWordsRec(root, "", words);

    return words;
}

void Dawg::printWords() const
{
    vector<string> words = getWords();
    for (string word : words) {
        cout << word << endl;
    }

    if (words.size() == 0) {
        cout << "Empty dawg" << endl;
    }
}

void Dawg::eraseNode(DawgNode* node)
{
    //cout << *node << endl;

    for (Edge* edge : node->getChildEdges()) {
        DawgNode* childNode = edge->getDestination();

        //do not delete the child node if it has multiple parents
        //this lets the function delete single branches/words instead of entire suffixes
        if (childNode->getNumParents() <= 1) {
            eraseNode(childNode);
        }
        else {
            for (Edge* parents : childNode->getParentsEdges()) {
                if (parents->getDestination() == node) {
                    delete parents;
                }
            }
        }

        delete edge;
        
    }
    for (Edge* parentEdge : node->getParentsEdges()) {
        delete parentEdge;
    }
    delete node;
}

void Dawg::getWordsRec(DawgNode* node, string prefix, vector<string>& wordList) const {
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
