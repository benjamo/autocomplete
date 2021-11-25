#pragma once
#include <map>
#include <vector>

/**
* Class TrieNode
* 
*  class for node of Trie each node contains
*  1.the mapping of letter to node and
*  2.whether the current node is the end of word or not.
*/
class TrieNode {

    private:
        std::map<char, TrieNode*> children;
        bool endOfWord;

    public:
        TrieNode();
        TrieNode* setChild(char letter);
        void setEndOfWord(bool val);
        bool getEndOfWord();
        TrieNode* getChild(char letter);
        void removeChild(char letter);
        bool hasChildren();
        std::vector<char> getChildrenKeys();
        int getNumOfChildren();
        ~TrieNode();

};