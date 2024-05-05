#include "Dawg.h"
#include <algorithm>

Edge::Edge(char letter, TrieNode* start, TrieNode* destination) {
    this->letter = letter;
    this->start = start;
    this->destination = destination;
}

Edge::Edge(TrieNode* parent, TrieNode* child) {
    this->letter = ' ';
    this->start = parent;
    this->destination = child;
}
//end Edge
//---------------------------------------------------------------------------------------------------
//begin TrieNode

TrieNode::TrieNode() {
    terminal = false;
}

void TrieNode::addParent(TrieNode* node) {
    Edge* edge = new Edge(' ', this, node);
    parents.push_back(edge);
}


//void TrieNode::redirect(TrieNode* node)
//{
//    char letter = this->getChildEdges().at(0)->getLetter();
//
//    Edge* edgeReverse = new Edge(' ', node, this);
//    node->parents.push_back(edgeReverse);
//
//    Edge* edge = new Edge(letter, this, node);
//    this->children.push_back(edge);
//}

TrieNode* TrieNode::addChild(char letter) {
    TrieNode* newNode = new TrieNode();
    Edge* edge = new Edge(letter, this, newNode);
    children.push_back(edge);
    newNode->addParent(this);
    return newNode;
}

set<TrieNode*> TrieNode::getChildrenNodes() const {
    set <TrieNode*> nodes;

    for (Edge* child : children) {
        nodes.insert(child->getDestination());
    }

    return nodes;
}

vector<TrieNode*> TrieNode::getParentNodes() const {
    set <TrieNode*> nodes;

    for (Edge* parent : parents) {
        nodes.insert(parent->getDestination());
    }

    vector <TrieNode*> vectorNodes(nodes.begin(), nodes.end());

    return vectorNodes;
}

void TrieNode::removeChildEdge(Edge* edge)
{
    auto position = std::find(children.begin(), children.end(), edge);
    children.erase(position);
}

void TrieNode::removeParentEdge(Edge* edge)
{
    auto position = std::find(parents.begin(), parents.end(), edge);
    parents.erase(position);
}

bool TrieNode::hasEdge(char letter) {
    for (Edge* child : children) {
        if (child->getLetter() == letter) {
            return true;
        }
    }

    return false;
}

Edge* TrieNode::getEdge(char letter) {
    for (Edge* child : children) {
        if (child->getLetter() == letter) {
            return child;
        }

    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const TrieNode& obj) {
    os << "TrieNode value: ";
    auto children = obj.getChildEdges();
    for (int i = 0; i < children.size(); i++) {
        os << children.at(i)->getLetter();
    }

    return os;
}

//end TrieNode
//---------------------------------------------------------------------------------------------------
//begin Trie

Trie::Trie(vector<string> wordList) {
    //lastAdded = nullptr;
    addWords(wordList);
}

Trie::Trie(const Trie& dawg)
{
    //lastAdded = nullptr;
    this->addWords(dawg.getWords());
}

Trie& Trie::operator=(const Trie& other)
{
   
    if (this != &other) {
        this->clear();
        if (other.getWords().size() != 0) {
            this->addWords(other.getWords());
        }
    }

    return *this;
}

//words are passed in, in reverse alphabetical order for this method
void Trie::addWord(string word) {
    if (root == nullptr) {
        root = new TrieNode();
    }

    TrieNode* currentNode = findPrefixNode(word);
    int lengthPre = findPrefixString(word).length();

    //need to have temporary storage for lastAdded so we can only change lastAdded after calling reduce
    //without this temp storage, lastAdded = currentNode in reduce
    //TrieNode* tempLastAdded = lastAdded;

    for (int i = lengthPre; i < word.length(); i++) {
        currentNode = currentNode->addChild(word.at(i));
        //tempLastAdded = currentNode;
    }
    currentNode->setTerminal(true);
    
    //reduce(currentNode);

    //lastAdded = tempLastAdded;
}


void Trie::addWords(vector<string> words)
{
    //sort words in reverse order before adding them
    //this ensures greater efficiency when adding nodes
    std::sort(words.begin(), words.end(), std::greater<>());

    for (string word : words) {
        addWord(word);
    }
}

//void Trie::reduce(TrieNode* current) {
//    // Not implemented yet
//    if (lastAdded == nullptr) {
//        return;
//    }
//
//    vector <string> lastAddedRight;
//    vector <string> currentRight;
//
//    this->getWordsRec(lastAdded, "", lastAddedRight);
//    this->getWordsRec(current, "", currentRight);
//
//    TrieNode* currentParent = current;
//
//    while (lastAddedRight == currentRight && lastAdded->getTerminal() == currentParent->getTerminal()) {
//        currentParent = currentParent->getParentNodes().at(0);
//
//        //redirect edge
//        currentParent->redirect(lastAdded);
//
//        for (Edge* edgeOfParent : currentParent->getChildEdges()) {
//            if (edgeOfParent->getDestination() == current) {
//                currentParent->removeChildEdge(edgeOfParent);
//                //delete edgeOfParent;
//            }
//        }
//        //delete old node
//        eraseNode(current);
//
//        if (lastAdded->getNumParents() == 0) {
//            return;
//        }
//
//        //set last Added and current 
//        lastAdded = lastAdded->getParentNodes().at(0); //assuming its the first parent
//        current = currentParent;
//
//        lastAddedRight.clear();
//        currentRight.clear();
//
//        this->getWordsRec(lastAdded, "", lastAddedRight);
//        this->getWordsRec(currentParent, "", currentRight);
//
//    }
//
//}


TrieNode* Trie::clear()
{
    eraseNode(root);
    root = new TrieNode();
    //lastAdded = nullptr;
    return root;
}

string Trie::findPrefixString(string word) {
    TrieNode* currentNode = root;
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

TrieNode* Trie::findPrefixNode(string word) {
    TrieNode* currentNode = root;
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

vector<string> Trie::getWords() const
{
    vector<string> words;

    //pass words by reference
    getWordsRec(root, "", words);

    return words;
}

void Trie::printWords() const
{
    vector<string> words = getWords();
    for (string word : words) {
        cout << word << endl;
    }

    if (words.size() == 0) {
        cout << "Empty dawg" << endl;
    }
}

void Trie::prune(string guessInfo, string guess)
{
    //store guessInfo for double letters and create seperate methods for each case
    //finish yellows functionality
    for (int i = 0; i < guessInfo.length(); i++) {
        bool doubleLetter = false;
        for (int k = 0; k < guess.length(); k++) {
            if (k != i && guess[k] == guess[i]) {
                doubleLetter = true;
            }
        }
        if (guessInfo[i] == 'Y') {
            pruneGreen(guess[i], i);
        }
        else if (guessInfo[i] == 'M') {
            pruneYellow(guess[i], i);
        }

        else if (guessInfo[i] == 'N') {
            if (!doubleLetter) {
                pruneGrey(guess[i]);
            }
        }
    }
}

void Trie::pruneGreen(char letter, int idx)
{
    pruneGreenRec(letter,0, idx, root);
}

void Trie::pruneGreenRec(char letter,int currentIdx, int targetIdx, TrieNode* node)
{
    if (currentIdx > targetIdx) {
        return;
    }
    else {
        for (Edge* childEdge : node->getChildEdges()) {
            if (currentIdx == targetIdx && childEdge->getLetter() != letter) {
                eraseNode(childEdge->getDestination());
                node->removeChildEdge(childEdge);
            }
            else {
                pruneGreenRec(letter, currentIdx + 1, targetIdx, childEdge->getDestination());
            }
        }
    }
    
}

void Trie::pruneYellow(char letter, int idx)
{
    pruneYellowRec(letter, 0, idx, root);
}

void Trie::pruneYellowRec(char letter, int currentIdx, int targetIdx, TrieNode* node)
{
    //removing words with yellow letter in wrong spot
    if (currentIdx == targetIdx) {
        for (Edge* childEdge : node->getChildEdges()) {
            if (childEdge->getLetter() == letter) {
                eraseNode(childEdge->getDestination());
                node->removeChildEdge(childEdge);
            }
        }
    }

    //removing words without yellow letter
    else {

    }

    for (Edge* childEdge : node->getChildEdges()) {
        pruneYellowRec(letter, currentIdx + 1, targetIdx, childEdge->getDestination());
    }
    
}

void Trie::pruneGrey(char letter)
{
    pruneGreyRec(letter, root);
}

void Trie::pruneGreyRec(char letter, TrieNode* node)
{
    for (Edge* childEdge : node->getChildEdges()) {
        if (childEdge->getLetter() == letter) {
            eraseNode(childEdge->getDestination());
            node->removeChildEdge(childEdge);
        }
        else {
            pruneGreyRec(letter, childEdge->getDestination());
        }
    }


}

void Trie::pruneByIdx(char letter, int idx)
{
    
}

void Trie::pruneByIdxRec(char letter, int currentIdx, int targetIdx, TrieNode* node)
{
}


void Trie::eraseNode(TrieNode* node)
{
    //cout << *node << endl;

    for (Edge* edge : node->getChildEdges()) {
        TrieNode* childNode = edge->getDestination();

        //do not delete the child node if it has multiple parents
        //this lets the function delete single branches/words instead of entire suffixes
        if (childNode->getNumParents() <= 1) {
            eraseNode(childNode);
        }
        else {
            for (Edge* parentEdge : childNode->getParentsEdges()) {
                if (parentEdge->getDestination() == node) {
                    //cout << "     removing " << edge->getLetter() << " edge" << endl;
                    childNode->removeParentEdge(parentEdge);
                    node->removeChildEdge(edge);
                }
            }
        }

        //delete edge;
        
    }
    for (Edge* parentEdge : node->getParentsEdges()) {
        node->removeParentEdge(parentEdge);
    }

    delete node;
}

void Trie::getWordsRec(TrieNode* node, string prefix, vector<string>& wordList) const {
    if (node == nullptr) {
        return;
    }

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
