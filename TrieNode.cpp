#include "TrieNode.h"

/**
* Simple constructor for class
* 
*/
TrieNode::TrieNode() { 
    endOfWord = false; 
}

/**
* Adds a link for a letter in current node
* 
* @param char letter
* 
* @return TrieNode*
*/
TrieNode* TrieNode::setChild(char letter) {
    TrieNode* newNode = new TrieNode();
    children.insert(std::pair<char, TrieNode*>(letter, newNode));
    return newNode;
}

/**
* Sets EndOfWord variable depending upon
* if current node is end of word or not.
* 
* @param bool value
* 
* @return void
*/
void TrieNode::setEndOfWord(bool value) {
    endOfWord = value;
}

/**
* Returns end of word value
*
* @return bool
*/
bool TrieNode::getEndOfWord() {
    return endOfWord; 
}

/**
* Returns the node associated to the letter
* returns nullptr if no such letter exists
* 
* @param char letter
* 
* @return TrieNode*
*/
TrieNode* TrieNode::getChild(char letter) {

    if (children.find(letter) != children.end()) {
        return children[letter];
    } else {
        return nullptr;
    }

}

/**
* Removing the corresponding child node
* of current node.
* 
* @param char letter
* 
* @return void
*/ 
void TrieNode::removeChild(char letter) {
    delete children[letter];
    children.erase(letter);
}

/**
* Returns true if current node
* has any children
* 
* @return bool
*/
bool TrieNode::hasChildren() {

    if (children.size() == 0) {
        return false;
    } else {
        return true;
    }
}

/**
* Gets all the letters that are the children
* of current node.
* 
* @return std::vector<char>
*/
std::vector<char> TrieNode::getChildrenKeys() {

    std::vector<char> keys;

    for (auto element : children) {
        keys.push_back(element.first);
    }

    return keys;
}

/**
* Gets the number of children
* of current node.
* 
* @return int
*/
int TrieNode::getNumOfChildren() { 
    return children.size(); 
}


/**
* Destructor
*
*/
TrieNode::~TrieNode() {
}