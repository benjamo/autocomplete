#include "Trie.h"
#include <stdexcept>

/**
* Constructor
*
* @return void
*/
Trie::Trie() {

    root = new TrieNode();
    root->setEndOfWord(false);

}

/**
* Constructor
*
* @param std::string filename
*
* @return void
*/
Trie::Trie(std::string filename) {

    root = new TrieNode();
    root->setEndOfWord(false);

    std::ifstream trieFile(filename);

    if (!trieFile.is_open()) {
        throw std::runtime_error("No deserialisation occured as filename doesnt exist.");
    } else {
        deserialise(root, trieFile);
    }

}

/**
* Destructor
*
* @param TrieNode* node
* @param std::fstream& s
*
* @return void
*/
Trie::~Trie() { 
    delete root;
}

/**
* Deserialise
*
* @param TrieNode* node
* @param std::fstream& s
*
* @return void
*/
void Trie::deserialise(TrieNode* node, std::ifstream& s) {

    std::string curWord;

    int numChildren;

    // get EOW
    getline(s, curWord, ' ');

    if (curWord == "0") {
        node->setEndOfWord(false);
    } else {
        node->setEndOfWord(true);
    }

    // get number of children

    if (!getline(s, curWord, ' ')) {
        throw "File is empty.";
    };

    numChildren = stoi(curWord);

    int index = 0;

    while (index < numChildren) {

        getline(s, curWord, ' ');
        node->setChild(curWord[0]);
        deserialise(node->getChild(curWord[0]), s);
        index++;

    }

}

/**
* Insert word into trie
*
* @param std::string word
*
* @return void
*/
void Trie::insertWord(std::string word) {
    
    TrieNode* curNode = root;

    int wordLength = word.length();
    int index = 0;

    // finding the position for insertion of word
    // looking through nodes,if not present
    // creting new ones.
    while (index < wordLength) {

        char curLetter = word[index];
        TrieNode* childNode = curNode->getChild(curLetter);

        if (childNode == nullptr) {
            childNode = curNode->setChild(curLetter);
        }

        curNode = childNode;
        index++;
    }

    // setting endOfWord=True for cuurent node
    // to denote end of word
    curNode->setEndOfWord(true);
}

/**
* Insert word list
*
* @param std::vectory<std::string> wordList
*
* @return void
*/
void Trie::insertWordList(std::vector<std::string> wordList) {

    for (auto word : wordList) {
        insertWord(word);
    }

}

/**
* Load words
*
* @param std::string filename
*
* @return bool
*/
bool Trie::loadWords(std::string filename) {

    std::ifstream wordFile(filename);

    if (!wordFile.is_open()) {
        throw std::runtime_error("Could not open file");
        return false;
    } else {

        std::vector<std::string> wordList;
        std::string word;

        while (!wordFile.eof()) {
            wordFile >> word;
            wordList.push_back(word);
        }

        insertWordList(wordList);
        return true;
    }

}

/**
* Check whether word exists in trie
*
* @param std::string word
*
* @return void
*/
bool Trie::wordExists(std::string word) {

    TrieNode* curNode = root;

    int wordLength = word.length();
    int index = 0;

    while (index < wordLength) {

        TrieNode* childNode = curNode->getChild(word[index]);

        if (childNode == nullptr) {
            return false;
        }

        curNode = childNode;
        index++;
    }

    return curNode->getEndOfWord();
}

/**
* Delete word
* 
* this method deletes a word from trie
* the word may have a another word
* as child, thus, the nodes for that word cant be removed
* if no child we keep removing nodes
* until we reach a node that has a child
* or is end of a word.
* removing nodes happen in the reverse order
* meaning node farthest from root is removed first.
* 
* @param std::string word
*
* @return void
*/
void Trie::deleteWord(std::string word) {

    // first, we reach the endofword for the word,
    // while storing the path nodes in stack.
    // if word doesnt exist, then print so.
    std::stack<TrieNode*> nodeStack;
    TrieNode* childNode, * curNode = root;

    int index = 0;
    int wordLength = word.length();

    while (index < wordLength) {

        nodeStack.push(curNode);
        childNode = curNode->getChild(word[index]);

        if (childNode == nullptr) {
            throw std::runtime_error("No such word exixts");
            return;
        }

        curNode = childNode;
        index++;
    }

    // curNode has the value of EOW for
    // this current word
    // setting EOW for this node to false,
    // to denote removal of word
    curNode->setEndOfWord(false);

    // if last node has children,
    // then we cant delete any node.
    if (!curNode->hasChildren()) {

        int index = 0;

        while (!nodeStack.empty()) {

            curNode = nodeStack.top();
            nodeStack.pop();

            std::cout << "deleting letter....\n" << word[wordLength - index - 1] << std::endl;
            curNode->removeChild(word[wordLength - index - 1]);
            index++;

            // if that node has endOfWord==true or hasChildren>0
            // then other we cant delete nodes anymore.
            // as haschildren>0 means other nodes are linked to it.
            // and EOW==true means this node is end of word for some word
            if (curNode->getEndOfWord() || curNode->getNumOfChildren() > 0) {
                break;
            }
        }
    }
}

/**
* Get suggestions
* 
* getting a word, and displaying all the words in trie that have that word
* as a prefix.
* 
* @param std::string word
*
* @return void
*/
void Trie::getSuggestions(std::string word) {

    // traverse the trie,until the given word
    // is exhausted. The node reached can be used for
    // finding required words, as its children will
    // contain words which have our argument word as prefix.
    TrieNode* curNode = root, *childNode;
    int index = 0;
    int wordLength = word.length();

    while (index < wordLength) {

        childNode = curNode->getChild(word[index]);

        if (childNode == nullptr) {
            throw std::runtime_error("No suggestions found");
            return;
        }

        index++;
        curNode = childNode;

    }

    // now curNode contains the node whose children are suggestions.
    std::vector<std::string> suggestionsList;
    std::vector<std::string>::iterator it;
    getSuggestionsHelper(curNode, suggestionsList, word);

    char delimiter;

    for (it = suggestionsList.begin(); it != suggestionsList.end(); it++) {

        if (it + 1 == suggestionsList.end()) {
            delimiter = ' ';
        } else {
            delimiter = ',';
        }

        std::cout << *it << delimiter;
    }

    std::cout << std::endl;
}

/**
* Suggestions helper
*
* @param TrieNode* node
* @param std::fstream& s
*
* @return void
*/
void Trie::getSuggestionsHelper(
    TrieNode* curNode,
    std::vector<std::string>& suggestionsList,
    std::string subWord
) {

    if (curNode->getEndOfWord()) {
        suggestionsList.push_back(subWord);
    }

    std::vector<char>::iterator it;
    std::vector<char> keys = curNode->getChildrenKeys();

    for (it = keys.begin(); it != keys.end(); it++) {
        getSuggestionsHelper(curNode->getChild(*it), suggestionsList, subWord + (*it));
    }

}

/**
* Display trie
*
* @return void
*/
void Trie::displayTrie() {

    std::stringstream buffer;
    displayTrieHelper(root, '$', buffer, "", "");
    std::cout << buffer.str() << std::endl;

}

/**
* Display trie helper
*
* @param TrieNode* curNode
* @param char val
* @param std::stringstream& buffer
* @param std::string prefix
* @param std::string childrenPrefix
*
* @return void
*/
void Trie::displayTrieHelper(
    TrieNode* curNode,
    char val,
    std::stringstream& buffer,
    std::string prefix,
    std::string childrenPrefix
) {

    buffer << prefix;
    buffer << val;
    buffer << '\n';

    std::vector<char>::iterator it;
    std::vector<char> keys = curNode->getChildrenKeys();

    for (it = keys.begin(); it != keys.end();) {

        char curVal;

        if (*it == ' ') {
            curVal = '_';
        } else {
            curVal = *it;
        }

        if ((it + 1) != keys.end()) {

            displayTrieHelper(curNode->getChild(*it), curVal, buffer,
                childrenPrefix + "+--",
                childrenPrefix + "|  ");

        } else {

            displayTrieHelper(curNode->getChild(*it), curVal, buffer,
                childrenPrefix + "+--",
                childrenPrefix + "   ");

        }

        it++;
    }
}

/**
* Serialise trie
*
* @return void
*/
void Trie::serialiseTrie() {

    std::fstream trieFile;
    trieFile.open("myTrie.txt", std::ios::out | std::ios::trunc);

    if (!trieFile) {
        throw std::runtime_error("File could not be created");
    } else {

        serialiseTrieHelper(root, trieFile);
        trieFile.close();

    }

}

/**
* Serialise trie helper
* 
* @param TrieNode* node
* @param std::fstream& s
* 
* @return void
*/
void Trie::serialiseTrieHelper(TrieNode* node, std::fstream& s) {

    s << node->getEndOfWord();
    s << ' ';

    int num = node->getNumOfChildren();
    std::vector<char> keys = node->getChildrenKeys();
    s << num;
    s << ' ';

    int index = 0;

    while (index < num) {
        s << keys[index];
        s << ' ';
        serialiseTrieHelper(node->getChild(keys[index]), s);
        index++;
    }

}
