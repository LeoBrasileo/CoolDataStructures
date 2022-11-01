#ifndef _LISTA_ALUMNOS_H_
#define _LISTA_ALUMNOS_H_

#include <string>
#include <ostream>

using namespace std;

typedef unsigned long Nat;

class List {
public:

    /**
     * Constructor por defecto de la clase List.
     */
    List();

    /**
     * Constructor por copia de la clase List.
     */
    List(const List& l);

    /**
     * Destructor de la clase List.
     */
    ~List();

    /**
     * Operador asignacion
     * @param aCopiar
     * @return
     */
    List& operator=(const List& aCopiar);

    /**
     * Agrega un elemento al principio de la List.
     * @param elem elemento a agregar
     */
    void pushFront(const int& elem);

    /**
     * Agrega un elemento al final de la List.
     * @param elem elemento a agregar
     */
    void pushBack(const int& elem);

    /**
     * Elimina el i-ésimo elemento de la List.
     * @param i posición del elemento a remove
     */
    void remove(Nat i);

    /**
     * Devuelve la cantidad de elementos que contiene la List.
     * @return
     */
    int length() const;

    /**
     * Devuelve el elemento en la i-ésima posición de la List.
     * @param i posición del elemento a devolver.
     * @return referencia no modificable
     */
    const int& iesimo(Nat i) const;
    /**
     * Devuelve el elemento en la i-ésima posición de la List.
     * @param i posición del elemento a devolver.
     * @return referencia modificable
     */
    int& iesimo(Nat i);

    /**
     * Muestra la lista en un ostream
     * formato de salida: [a_0, a_1, a_2, ...]
     * @param o
     */
    void show(ostream& o);

    /**
     * Utiliza el método show(os) para sobrecargar el operador <<
     */
    friend ostream& operator<<(ostream& os, List& l) {
        l.show(os);
        return os;
    }

private:

    struct Node {
        int value;
        Node* bef;
        Node* next;

        Node(int v, Node* a, Node* s) : value(v), bef(a), next(s) {}
    };

    Node* _first;
};

#endif
