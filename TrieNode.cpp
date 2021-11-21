#include "TrieNode.h"

/**
* simple constructor for class
* 
*/
TrieNode::TrieNode() { 
    endOfWord = false; 
}

/**
* adds a link for a letter in current node
*
*/
TrieNode* TrieNode::setChild(char letter) {
    TrieNode* newNode = new TrieNode();
    children.insert(std::pair<char, TrieNode*>(letter, newNode));
    return newNode;
}

/**
* sets EndOfWord variable depending upon
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
* returns the node associated to the letter
* returns nullptr if no such letter exists
*/
TrieNode* TrieNode::getChild(char letter) {

    if (children.find(letter) != children.end()) {
        return children[letter];
    } else {
        return nullptr;
    }

}

/**
* removing the corresponding child node
* of current node.
*/ 
void TrieNode::removeChild(char letter) {
    delete children[letter];
    children.erase(letter);
}

/**
* returns true if current node
* has any children
*/
bool TrieNode::hasChildren() {

    if (children.size() == 0) {
        return false;
    } else {
        return true;
    }
}

/**
* gets all the letters that are the children
*  of current node.
*/
std::vector<char> TrieNode::getChildrenKeys() {

    std::vector<char> keys;

    for (auto element : children) {
        keys.push_back(element.first);
    }

    return keys;
}

/**
* gets the number of children
* of current node.
*/
int TrieNode::getNumOfChildren() { 
    return children.size(); 
}
