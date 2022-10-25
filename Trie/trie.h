#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H
#include <string>

using namespace std;

const int alphabetSize = 25;

class Trie {
public:
    Trie();
    void insert(string word);
    bool search(string word);
private:
    Trie* _values [alphabetSize + 1];
    //Trie* _first;
};


#endif //TRIE_TRIE_H
