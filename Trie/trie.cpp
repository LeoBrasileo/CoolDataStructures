#include "trie.h"
#include <stdio.h>
#include <string.h>

//enum alphabet {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};

Trie::Trie() {
    for (int i = 0; i < alphabetSize + 1; i++) {
        this->_values[i] = nullptr;
    }
}

void Trie::insert(std::string word) {
    Trie* curr = this;
    for(int i = 0; i < word.length(); i++){
        char x = word[i];
        int charPosition = x - 'a';
        if (curr->_values[charPosition] == nullptr){
            curr->_values[charPosition] = new Trie();
        }
        curr = curr->_values[charPosition];

        if(i + 1 == word.length()){
            curr->_values[alphabetSize] = curr;
        }
    }
}

bool Trie::search(std::string word) {
    Trie* curr = this;
    int i = 0;
    for(i; i < word.length(); i++){
        char x = word[i];
        int charPosition = x - 'a';
        if (curr->_values[charPosition] == nullptr){
            return false;
        }

        curr = curr->_values[charPosition];
    }

    if(i == word.length() && curr->_values[alphabetSize] == curr){
        return true;
    }
}