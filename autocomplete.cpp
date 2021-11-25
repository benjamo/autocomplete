/**
* autocomplete.cpp
* 
* 
*/

#include "TrieNode.h"
#include "Trie.h"

int getNumber(std::ifstream& s) { 
    return 0;
}
const std::string FILENAME = "myTrie.txt";

int main() {

    std::string welcome = "========================================================";

    std::string menu =
        "\nOptions:\
        \n1. Load words from word file\
        \n2. Add a word\
        \n3. Display Trie\
        \n4. Delete Word\
        \n5. Get Suggestions\
        \n6. Exit\n";

    std::cout << welcome << std::endl;

    Trie *trie = new Trie(FILENAME);
    std::cout << menu;
    std::cout << "====>Enter the option" << std::endl;
    std::cout << ">>";

    int option;

    bool running = true;

    while (running) {

        std::cin >> option;

        try {

            switch (option) {

                case 1: {
                    std::string wordFilename;
                    std::cout << "Enter the name of txt file(without extension)>>";
                    std::cin >> wordFilename;
                    std::cout << "Loading Words............\n";

                    delete trie;
                    trie = new Trie();

                    bool success = trie->loadWords(wordFilename + ".txt");

                    if (success) {
                        std::cout << "Loaded Words!!!\n";
                    }
                    break;
                }
                case 2: {
                    std::cout << "Enter the word\n>>";
                    std::string word;
                    std::cin >> word;
                    trie->insertWord(word);
                    break;
                }
                case 3: {
                    trie->displayTrie();
                    break;
                }
                case 4: {
                    std::cout << "Enter the word\n>>";
                    std::string word;
                    std::cin >> word;
                    trie->deleteWord(word);
                    break;
                }
                case 5: {
                    std::cout << "Enter the word\n>>";
                    std::string word;
                    std::cin >> word;
                    trie->getSuggestions(word);
                    break;
                }
                case 6: {
                    running = false;
                    trie->serialiseTrie();
                    trie->~Trie();
                    break;
                }
                default: {
                    std::cout << "Enter valid option\n";
                    break;
                }
            }
        } catch (std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }

        if (running) {
            std::cout << menu + "====>Enter the option" << std::endl << ">>";
        }
    }
}

