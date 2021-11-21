#pragma once
#include <map>
#include <vector>

class TrieNode {
    // class for node of Trie
    // each node contains
    // 1.the mapping of letter to node and
    // 2.whether the current node is the end of word or not.

private:
    std::map<char, TrieNode*> children;
    bool endOfWord;

public:
    // simple constructor for class
    TrieNode();

    // adds a link for a letter in current node
    TrieNode* setChild(char letter);

    // sets EOW(end of word val) depending upon
    // if current node is end of word or not.
    void setEndOfWord(bool val);

    // fetches EOW value
    bool getEndOfWord();

    // returns the node associated to the letter
    // returns nullptr if no such letter exists
    TrieNode* getChild(char letter);

    // removing the corresponding child node
    // of current node.
    void removeChild(char letter);

    // returns true if current node
    // has any children
    bool hasChildren();

    // gets all the letters that are the children
    // of current node.
    std::vector<char> getChildrenKeys();

    // gets the number of children
    // of current node.
    int getNumOfChildren();

};