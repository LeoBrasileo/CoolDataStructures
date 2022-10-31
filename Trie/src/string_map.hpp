
#include "string_map.h"

template <typename T>
string_map<T>::string_map() : root(new Node(nullptr)), _size(0) {}

template <typename T>
string_map<T>::string_map(const string_map<T>& toCopy) {
    *this = toCopy;
}

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    Node* n = copy(d.root, nullptr);
    int tam = d._size;
    this->root = n;
    this->_size = tam;
}

template<typename T>
typename string_map<T>::Node *string_map<T>::copy(string_map::Node *toCopy, string_map::Node *parent) {
    T* ndef = toCopy->definition != nullptr ? new T(*toCopy->definition) : nullptr;
    Node* n = new Node(ndef, parent);
    n->nexts = toCopy->nexts;
    for(int i = 0; i < alphSize; i++){
        if (n->nexts[i] != nullptr)
            n->nexts[i] = copy(n->nexts[i], n);
    }

    return n;
}

template <typename T>
string_map<T>::~string_map(){
    recursiveDestruction(root);
}

template <typename T>
void string_map<T>::recursiveDestruction(string_map::Node* curr) {
    if (curr != nullptr){
        delete curr->definition;
        for(int i = 0; i < alphSize; i++)
            recursiveDestruction(curr->nexts[i]);

        delete curr;
    }
}

template<typename T>
void string_map<T>::insert(const pair<string, T> & obj) {
    Node* curr = root;
    string key = obj.first;
    T* def = new T(obj.second);
    int i;
    for (i = 0; i < key.size(); i++){
        int pos = int(key[i]);
        if (curr->nexts[pos] == nullptr){
            curr->nexts[pos] =  new Node(curr);
        }
        curr = curr->nexts[pos];
    }
    if (curr->definition == nullptr)
        _size++;
    else
        delete curr->definition;

    curr->definition = def;
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    Node* curr = root;
    int i = 0;
    while (i < clave.size()){
        int pos = int(clave[i]);
        if (curr->nexts[pos] == nullptr){
            return 0;
        }
        curr = curr->nexts[pos];
        i++;
    }

    if (curr->definition != nullptr){
        return 1;
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Node* curr = root;
    int i = 0;
    while (i < clave.size()){
        int pos = int(clave[i]);
        curr = curr->nexts[pos];
        i++;
    }

    return *curr->definition;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Node* curr = root;
    int i = 0;
    while (i < clave.size()){
        int pos = int(clave[i]);
        if (curr->nexts[pos] == nullptr){
            curr->nexts[pos] =  new Node(curr);
        }
        curr = curr->nexts[pos];
        i++;
    }

    if (curr->definition == nullptr)
        curr->definition = new T();

    return *curr->definition;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    this->at(clave);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Node* curr = root;
    int i = 0;
    while (i < clave.size()){
        int pos = int(clave[i]);
        curr = curr->nexts[pos];
        i++;
    }

    delete curr->definition;
    curr->definition = nullptr;

    while (curr->parent != nullptr){
        bool useless = uselessNode(curr);
        Node* par = curr->parent;
        if (useless){
            for (int j = 0; j < alphSize; j++){
                if (curr->parent->nexts[j] == curr)
                    curr->parent->nexts[j] = nullptr;
            }
            delete curr;
        }
        curr = par;
    }
}

template <typename T>
bool string_map<T>::uselessNode(string_map::Node* curr) {
    Node* son;
    int childs = 0;
    for (int j = 0; j < alphSize; j++){
        if (curr->nexts[j] != nullptr){
            childs++;
            son = curr->nexts[j];
        }
    }
    if (childs > 1) {return false; }
    return (childs == 0 && curr->definition == nullptr) || (childs == 1 && uselessNode(son));
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return size() == 0;
}
