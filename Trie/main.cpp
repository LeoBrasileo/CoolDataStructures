#include <iostream>
#include "trie.h"
#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
    Trie trie = Trie();
    trie.insert("hello");
    trie.insert("ghubabnsujdbu");
    trie.insert("hedasfgsadghsllo");
    trie.insert("fsdghdfhdfhdgfh");
    trie.insert("trgdfvcxvxz");
    trie.insert("pooihghuyvsad");
    trie.insert("jkhdafuehr");

    cout << "hello is in trie: " << trie.search("hello") << "\n";
    cout << "ghubabnsudbu is in trie: " << trie.search("ghubabnsudbu") << "\n";
    cout << "hedasfgsadghsllo is in trie: " << trie.search("hedasfgsadghsllo") << "\n";
    cout << "fsdghdfhdfhdgfh is in trie: " << trie.search("fsdghdfhdfhdgfh") << "\n";
    cout << "trgdfvcxvxz is in trie: " << trie.search("trgdfvcxvxz") << "\n";
    cout << "pooihghuyvsad is in trie: " << trie.search("pooihghuyvsad") << "\n";
    cout << "jkhdafuehr is in trie: " << trie.search("jkhdafuehr") << "\n";
    cout << "greg is in trie: " << trie.search("greg");
    return 0;
}
