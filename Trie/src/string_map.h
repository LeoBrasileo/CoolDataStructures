#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>

using namespace std;

const static int alphSize = 256;

template<typename T>
class string_map {
public:
    string_map();

    /**
    CONSTRUCTOR BY COPY
    **/
    string_map(const string_map<T>& toCopy);


    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();


    void insert(const pair<string, T>&);

    /**
    COUNT
    * retuns the ammount of appeaances of a key (1 or 0)
    **/

    int count(const string &key) const;

    const T& at(const string& key) const;
    T& at(const string& key);


    void erase(const string& key);

    int size() const;

    bool empty() const;

    T &operator[](const string &key);

private:

    struct Node {
        vector<Node*> nexts;
        Node* parent;
        T* definition;

        Node(Node* par) : nexts(alphSize, nullptr), definition(nullptr), parent(par) { }
        Node(T* def, Node* par) : nexts(alphSize, nullptr), definition(def), parent(par) { }
    };

    Node* copy (Node* toCopy, Node* parent);

    bool uselessNode (Node*);

    void recursiveDestruction (Node*);

    Node* root;
    int _size;
};

#include "string_map.hpp"

#endif // STRING_MAP_H_
