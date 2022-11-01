#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Set
{
    public:
        // Constructor. Genera un conjunto vacío.
        Set();

        // Destructor. Debe dejar limpia la memoria.
        ~Set();

        // Inserta un elemento en el conjunto. Si este ya existe,
        // el conjunto no se modifica.
        void insert(const T&);

        // Decide si un elemento in al conjunto o no.
        bool in(const T&) const;

        // Borra un elemento del conjunto. Si este no existe,
        // el conjunto no se modifica.
        void remove(const T&);

        // Siguiente elemento al recibido por párametro, en orden.
        // Pre: el elemento está en el conjunto y no es el máximo del conjunto.
        const T& next(const T& elem);

        // Devuelve el mínimo elemento del conjunto según <.
        const T& min() const;

        // Devuelve el máximo elemento del conjunto según <.
        const T& max() const;

        // Devuelve la cantidad de elementos que tiene el conjunto.
        unsigned int cardinal() const;

        // Muestra el conjunto.
        void show(std::ostream&) const;

        vector<T> inorder_keys();

    private:

        struct Node
        {
            // El elemento al que representa el nodo.
            T value;
            // Puntero a la raíz del subárbol izquierdo.
            Node* leftNode;
            // Puntero a la raíz del subárbol derecho.
            Node* rightNode;

            Node* parent;
            // El constructor, toma el elemento al que representa el nodo.
            Node(const T& v, Node* par) : value(v), leftNode(nullptr), rightNode(nullptr), parent(par) {};
        };

        int _cardinal(int count, Node* act) const;

        T& _min(Node* act) const;

        T& _max(Node* act) const;

        void _inorder_tree_walk_search_next(Node* nodo, const T& clave);
        void _inorder(Node* node, vector<T>*);
        T* _next;

        void recursiveDestruction(Node* act);

        // Puntero a la raíz de nuestro árbol.
        Node* _root;

};

template<class T>
std::ostream& operator<<(std::ostream& os, const Set<T>& c) {
    c.show(os);
	 return os;
}

#include "Set.hpp"

#endif // CONJUNTO_H_
