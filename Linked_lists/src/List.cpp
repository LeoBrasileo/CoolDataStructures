#include <cassert>
#include "List.h"

List::List() : _first(nullptr) {}

List::List(const List& l) : List() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

List::~List() {
    Node* actual = _first;
    while (actual != nullptr){
        Node* siguiente = actual->next;
        delete actual;
        actual = siguiente;
    }
    _first = nullptr;
}

List& List::operator=(const List& aCopiar) {
    Node* actual = _first;
    while (actual != nullptr){
        Node* siguiente = actual->next;
        delete actual;
        actual = siguiente;
    }
    _first = nullptr;

    actual = aCopiar._first;
    while (actual != nullptr){
        pushBack(actual->value);
        actual = actual->next;
    }
    return *this;
}

void List::pushFront(const int& elem) {
    Node* nuevo = new Node(elem, nullptr, _first);

    if (_first == nullptr){
        _first = nuevo;
        return;
    }

    //Apunto el anterior del segundo nodo de la lista al nuevo nodo de adelante
    Node* segu = _first->next;
    if (segu != nullptr){
        segu->bef = nuevo;
    }

    _first = nuevo;
}

void List::pushBack(const int& elem) {
    int i = 0, len = length();
    if (_first == nullptr && len == 0){
        pushFront(elem);
    } else{
        Node* actual = _first;
        while (i < len - 1){
            actual = actual->next;
            i++;
        }
        Node* nuevo = new Node(elem, actual, nullptr);
        actual->next = nuevo;
    }
}

void List::remove(Nat i) {
    int j = 0;
    Node* actual = _first;
    while (actual != nullptr){
        if (j == i) {
            Node* anterior = actual->bef;
            Node* siguiente = actual->next;
            if (actual == _first){
                _first = _first->next;
            }
            if (anterior != nullptr){
                anterior->next = siguiente;
            }
            if (siguiente != nullptr){
                siguiente->bef = anterior;
            }
            delete actual;
            return;
        }
        j++;
        actual = actual->next;
    }
}

int List::length() const {
    int len = 0;
    Node* actual = _first;
    while (actual != nullptr){
        len ++;
        actual = actual->next;
    }
    return len;
}

const int& List::iesimo(Nat i) const {
}

int& List::iesimo(Nat i) {
    int j = 0;
    static int res;
    Node* actual = _first;
    while (actual != nullptr){
        if (j == i) {
            res = actual->value;
        }
        j++;
        actual = actual->next;
    }
    return res;
}

void List::show(ostream& o) {
    o << "[" ;
    Node* actual = _first;
    while (actual != nullptr){
        o << actual->value << (actual->next != nullptr ? ", " : "");
        actual = actual->next;
    }
    o << "]";
}
