#include <cassert>
#include "Lista.h"

Lista::Lista() : _prim(nullptr) {}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    Nodo* actual = _prim;
    while (actual != nullptr){
        Nodo* siguiente = actual->sig;
        delete actual;
        actual = siguiente;
    }
    _prim = nullptr;
}

Lista& Lista::operator=(const Lista& aCopiar) {
    Nodo* actual = _prim;
    while (actual != nullptr){
        Nodo* siguiente = actual->sig;
        delete actual;
        actual = siguiente;
    }
    _prim = nullptr;

    actual = aCopiar._prim;
    while (actual != nullptr){
        agregarAtras(actual->valor);
        actual = actual->sig;
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevo = new Nodo(elem, nullptr, _prim);

    if (_prim == nullptr){
        _prim = nuevo;
        return;
    }

    //Apunto el anterior del segundo nodo de la lista al nuevo nodo de adelante
    Nodo* segu = _prim->sig;
    if (segu != nullptr){
        segu->ant = nuevo;
    }

    _prim = nuevo;
}

void Lista::agregarAtras(const int& elem) {
    int i = 0, len = longitud();
    if (_prim == nullptr  && len == 0){
        agregarAdelante(elem);
    } else{
        Nodo* actual = _prim;
        while (i < len - 1){
            actual = actual->sig;
            i++;
        }
        Nodo* nuevo = new Nodo(elem, actual, nullptr);
        actual->sig = nuevo;
    }
}

void Lista::eliminar(Nat i) {
    int j = 0;
    Nodo* actual = _prim;
    while (actual != nullptr){
        if (j == i) {
            Nodo* anterior = actual->ant;
            Nodo* siguiente = actual->sig;
            if (actual == _prim){
                _prim = _prim->sig;
            }
            if (anterior != nullptr){
                anterior->sig = siguiente;
            }
            if (siguiente != nullptr){
                siguiente->ant = anterior;
            }
            delete actual;
            return;
        }
        j++;
        actual = actual->sig;
    }
}

int Lista::longitud() const {
    int len = 0;
    Nodo* actual = _prim;
    while (actual != nullptr){
        len ++;
        actual = actual->sig;
    }
    return len;
}

const int& Lista::iesimo(Nat i) const {
}

int& Lista::iesimo(Nat i) {
    int j = 0;
    static int res;
    Nodo* actual = _prim;
    while (actual != nullptr){
        if (j == i) {
            res = actual->valor;
        }
        j++;
        actual = actual->sig;
    }
    return res;
}

void Lista::mostrar(ostream& o) {
    o << "[" ;
    Nodo* actual = _prim;
    while (actual != nullptr){
        o << actual->valor << (actual->sig != nullptr ? ", " : "");
        actual = actual->sig;
    }
    o << "]";
}
