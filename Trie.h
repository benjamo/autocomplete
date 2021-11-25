#pragma once

#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <vector>

#include "TrieNode.h"

/**
* Trie class
* 
*/
class Trie {

    private:
        TrieNode* root;

    public:
        Trie();
        Trie(std::string filename);
        void deserialise(TrieNode* node, std::ifstream& s);
        void insertWord(std::string word);
        void insertWordList(std::vector<std::string> wordList);
        bool loadWords(std::string filename);
        bool wordExists(std::string word);
        void deleteWord(std::string word);
        void getSuggestions(std::string word);
        void getSuggestionsHelper(TrieNode* curNode, std::vector<std::string>& suggestionsList, std::string subWord);
        void displayTrie();
        void displayTrieHelper(TrieNode* curNode, char val, std::stringstream& buffer, std::string prefix, std::string childrenPrefix);
        void serialiseTrie();
        void serialiseTrieHelper(TrieNode* node, std::fstream& s);
        ~Trie();
};