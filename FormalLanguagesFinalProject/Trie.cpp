#include "Trie.h"
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

int TrieNode::numLettersInParentBranch(char letter)
{
    string str = "";
    this->getParentContents(str);
    int i = 0;
    for (char strLetter : str) {
        if (strLetter == letter) {
            i++;
        }
    }

    return i;
}

//creates a str of the contents of the parent
void TrieNode::getParentContents(string& str)
{
    if (this->getNumParents() == 0) {
        reverse(str.begin(), str.end());
        return;
    }
    TrieNode* parentNode = this->getParentNodes()[0];
    Edge* startEdge = nullptr;
    for (Edge* edge : parentNode->getChildEdges()) {
        if (edge->getDestination() == this) {
            startEdge = edge;
        }
    }

    str += startEdge->getLetter();
    parentNode->getParentContents(str);
}


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
    delete edge;
    children.erase(position);
}

void TrieNode::removeParentEdge(Edge* edge)
{
    
    auto position = std::find(parents.begin(), parents.end(), edge);
    delete edge;
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
    addWords(wordList);
}

Trie::Trie(const Trie& dawg)
{
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


    for (int i = lengthPre; i < word.length(); i++) {
        currentNode = currentNode->addChild(word.at(i));
    }
    currentNode->setTerminal(true);
    
}


void Trie::addWords(vector<string> words)
{
    std::sort(words.begin(), words.end(), std::less<>());

    for (string word : words) {
        addWord(word);
    }
}


TrieNode* Trie::clear()
{
    eraseNode(root);
    root = new TrieNode();
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
        cout << "No words to print" << endl;
    }
}

//precondition: guessInfo and guess are the same length
void Trie::prune(string guessInfo, string guess)
{
    for (int i = 0; i < guessInfo.length(); ++i) {
        guess[i] = tolower(guess[i]);
        guessInfo[i] = toupper(guessInfo[i]);
    }

    //store guessInfo for duplicate letters and create seperate methods for each case

    //CASES FOR DUPLICATE LETTERS:
    // 
    // green i, grey i
    // vivid
    // ---------> means that there is an i at index 1 and no other i in the word
    //            
    // 
    // 
    // green i, yellow i
    // vivid
    // ---------> means that there's two i's
    //                  1 i @ index 1
    //                  1 i !@ index 3
    // 
    // 
    // yellow i, grey i
    // vivid
    // ---------> means that there is only 1 i, and it is in neither index 1 nor index 3
    // if triple letter with greys and yellows only we know number of yellows = number of char in word
    // and yellow and grey indices cannot have that char
    // 
    // Mult yellow i's 
    // vivid
    // ---------> means that there are two i's, and neither of them are in index 1 or 3
    //                                         (i must be in index 0, 2, or 4)
    // 
    // Mult grey i's
    // vivid
    // --------> easy! There is no i in the word (done)
    // 
    // 
    // Mult green i's
    // vivid
    // --------> easy! Just run green on both i's (done)
    //
    unordered_map<char, vector<int>> duplicates = findDuplicates(guess);

    for (int i = 0; i < guessInfo.length(); i++) {

        //if element is not found, mapElementIr == duplicates.end()
        //find() returns duplicates.end() (iterator after the last element) if element 
        //    does not exist in the map
        auto mapElementItr = duplicates.find(guess[i]);
        bool letterHasDuplicates = mapElementItr != duplicates.end();

        //simple pruning if no duplicates
        if (!letterHasDuplicates) {
            if (guessInfo[i] == 'Y') {
                pruneGreen(guess[i], i);
            }
            else if (guessInfo[i] == 'M') {
                pruneYellow(guess[i], i);
            }

            else if (guessInfo[i] == 'N') {
                pruneGrey(guess[i]);
            }
        }

        //deal with duplicate letters here
        else {
            vector<int> duplicateIndices = mapElementItr->second;

            int greenDuplicateCount = 0;  //Y
            int yellowDuplicateCount = 0; //M
            int greyDuplicateCount = 0;   //N

            //if all duplicate letters are grey, proceed as normal (call pruneGrey on the letter)
            bool allLettersGrey = true;
            for (int idx : duplicateIndices) {

                if (guessInfo[idx] == 'Y') { greenDuplicateCount++; }
                else if (guessInfo[idx] == 'M') { yellowDuplicateCount++; }
                else if (guessInfo[idx] == 'N') { greyDuplicateCount++; }
            }

            //if only duplicate greys
            if (yellowDuplicateCount == 0 && greenDuplicateCount == 0) {
                pruneGrey(guess[i]);
            }

            //if only duplicate greens
            else if (yellowDuplicateCount == 0 && greyDuplicateCount == 0) {
                pruneGreen(guess[i], i);
            }

            //duplicate yellows and greys
            else if (yellowDuplicateCount > 0 && greyDuplicateCount > 0 && greenDuplicateCount == 0) {
                //number of yellow's = number of that letter in word (no more or less)
                if (guessInfo[i] == 'M') {
                    pruneYellow(guess[i], i);
                }

                else if (guessInfo[i] == 'N') {
                    pruneByIdx(guess[i], i);
                }
                pruneByNumLetter(guess[i], yellowDuplicateCount);
            }
            //duplicate grey and green
            else if (greenDuplicateCount > 0 && greyDuplicateCount > 0 && yellowDuplicateCount == 0) {
                if (guessInfo[i] == 'Y') {
                    pruneGreen(guess[i], i);
                }
                else {
                    pruneByNumLetter(guess[i], greenDuplicateCount);
                }
            }
            //duplicate only yellows
            else if (greenDuplicateCount == 0 && greyDuplicateCount == 0) {
                pruneByIdx(guess[i], i);
                pruneByTooFewLetters(guess[i], yellowDuplicateCount);

            }

            //duplicate yellow and green
            else if (greenDuplicateCount > 0 && yellowDuplicateCount > 0 && greyDuplicateCount == 0) {
                if (guessInfo[i] == 'Y') {
                    pruneGreen(guess[i], i);
                }
                else if (guessInfo[i] == 'M') {
                    pruneByIdx(guess[i], i);
                }
                pruneByTooFewLetters(guess[i], yellowDuplicateCount + greenDuplicateCount);
            }

            //duplicate yellow, grey, and green
            else {
                if (guessInfo[i] == 'Y') {
                    pruneGreen(guess[i], i);
                }
                else if (guessInfo[i] == 'M' || guessInfo[i] == 'N') {
                    pruneByIdx(guess[i], i);
                }
                pruneByNumLetter(guess[i], yellowDuplicateCount + greenDuplicateCount);
            }
        }
    }
}

//modified from ChatGPT-produced function
//returns an unordered map where each element is a letter followed by the indices of duplicates
//ex. findDuplicates("hello") returns a map with one element: <'h', [2, 3]>
unordered_map<char, vector<int>> Trie::findDuplicates(const string& str) {
    unordered_map<char, vector<int>> charIndices;

    // Iterate through the string
    for (int i = 0; i < str.length(); ++i) {
        char ch = str[i];
        // Check if the character is already present
        if (charIndices.find(ch) != charIndices.end()) {
            // If yes, mark its index
            charIndices[ch].push_back(i);
        }
        else {
            // If no, add it to the map with its index
            charIndices[ch] = vector<int>{ i };
        }
    }

    //removes elements which only have 1 "duplicate"
    //ex. without this function, findDuplicates("hello") would contain <'h', [0]>, <'e', [1]>, etc.
    for (char letter : str) {
        if (charIndices.find(letter) != charIndices.end()) {
            auto mapElementVect = charIndices[letter];
            if (mapElementVect.size() == 1) {
                charIndices.erase(letter);
            }
        }
    }

    return charIndices;
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
#pragma omp parallel
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
    if (currentIdx == targetIdx) {
        pruneByIdx(letter, targetIdx);
    }

    //removing words without yellow letter
#pragma omp parallel
    for (Edge* childEdge : node->getChildEdges()) {
        TrieNode* childNode = childEdge->getDestination();
            
        //search to see if the target letter is in the childNode's right branches
        vector<string> rightBranchLangs;

        getWordsRec(childNode, "", rightBranchLangs);

        bool containsLetter = false;

        bool parentContainsLetter = childEdge->getLetter() == letter;

        //do not recurse if that branch has letter
        if (parentContainsLetter) {
            continue;
        }
           
        for (string word : rightBranchLangs) {
            for (char wordLetter : word) {
                if (wordLetter == letter) {
                    containsLetter = true;
                    break;
                }
            }
        }
           

        if (containsLetter) {
            //recurse down until you find a node you can cut
            pruneYellowRec(letter, currentIdx + 1, targetIdx, childNode);
        }
            //remove the node which has no children which contains target letter
        else {
            eraseNode(childNode);
            node->removeChildEdge(childEdge); 
        }
        

}
}

void Trie::pruneGrey(char letter)
{
    pruneGreyRec(letter, root);
}

void Trie::pruneByTooManyLetters(char letter, int target)
{
    pruneByTooManyLettersRec(letter, target, root, 0);
}

void Trie::pruneByTooManyLettersRec(char letter, int target, TrieNode* node, int lettersCounted)
{
    for (Edge* childEdge : node->getChildEdges()) {
        int oldNumLetters = lettersCounted;
        if (childEdge->getLetter() == letter) {
            lettersCounted++;
        }
        if (lettersCounted > target) {
            eraseNode(childEdge->getDestination());
            node->removeChildEdge(childEdge);
        }
        else  {
            pruneByTooManyLettersRec(letter, target, childEdge->getDestination(), lettersCounted);
        }

        lettersCounted = oldNumLetters;
    }

}

void Trie::pruneByTooFewLetters(char letter, int target)
{
    for (TrieNode* leaf : this->getLeaves()) {
        if (leaf == nullptr) {
            continue;
        }

        int numOfLetters = leaf->numLettersInParentBranch(letter);
        if (target > numOfLetters) {
           
            //delete edge
            TrieNode* parent = leaf->getParentNodes()[0];
            for (Edge* childEdge : parent->getChildEdges()) {
                if (childEdge->getDestination() == leaf) {
                    parent->removeChildEdge(childEdge);
                }
            }
            //delete leaf
            eraseNode(leaf);
            leaf->setTerminal(false);

        }
    }
}

vector<TrieNode*> Trie::getLeaves()
{
    vector<TrieNode*> leaves;
    getLeavesRec(root, leaves);
    return leaves;
}

void Trie::getLeavesRec(TrieNode* node, vector<TrieNode*>& leaves)
{
    if (node->getNumChildren() == 0) {
        leaves.push_back(node);
    }
    else {
        for (Edge* edge : node->getChildEdges()) {
            getLeavesRec(edge->getDestination(), leaves);
        }
    }
}

void Trie::pruneGreyRec(char letter, TrieNode* node)
{
#pragma omp parallel
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
    pruneByIdxRec(letter, 0, idx, root);
}

void Trie::pruneByIdxRec(char letter, int currentIdx, int targetIdx, TrieNode* node)
{
    if (currentIdx == targetIdx) {
        for (Edge* childEdge : node->getChildEdges()) {
            if (childEdge->getLetter() == letter) {
                eraseNode(childEdge->getDestination());
                node->removeChildEdge(childEdge);
            }
        }
    }
    
    else if (currentIdx < targetIdx) {
        for (TrieNode* childNode : node->getChildrenNodes()) {
            pruneByIdxRec(letter, currentIdx + 1, targetIdx, childNode);
        }
        
    }
}

void Trie::pruneByNumLetter(char letter, int target)
{
    pruneByTooManyLetters(letter, target);
    pruneByTooFewLetters(letter, target);

}


void Trie::eraseNode(TrieNode* node)
{
    for (Edge* edge : node->getChildEdges()) {
        TrieNode* childNode = edge->getDestination();

        //do not delete the child node if it has multiple parents
        //this lets the function delete single branches/words instead of entire suffixes
        if (childNode->getNumParents() <= 1) {
            eraseNode(childNode);
            node->removeChildEdge(node->getChildEdges().at(0));
        }
        else {
            for (Edge* parentEdge : childNode->getParentsEdges()) {
                if (parentEdge->getDestination() == node) {
                    childNode->removeParentEdge(parentEdge);
                    node->removeChildEdge(edge);
                }
            }
        }
    }

    /*while (node->getChildEdges().size() > 0) {
        node->removeChildEdge(node->getChildEdges().at(0));
    }*/

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
