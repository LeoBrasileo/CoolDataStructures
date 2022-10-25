
template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr), _siguiente(nullptr) {}

template <class T>
Conjunto<T>::~Conjunto() {
    destruccionRecursiva(_raiz);
}

template <class T>
void Conjunto<T>::destruccionRecursiva(Nodo* actual) {
    if (actual != nullptr){
        destruccionRecursiva(actual->izq);
        destruccionRecursiva(actual->der);
        delete actual;
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool res, menor = false;
    Nodo* act = _raiz;
    while (act != nullptr){
        if (act->valor == clave){
            return true;
        }
        menor = clave < act->valor;
        act = menor ? act->izq : act->der;
    }
    return res;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (pertenece(clave)){
        return;
    }
    Nodo* act;
    if (_raiz == nullptr){
        _raiz = new Nodo(clave, nullptr);
        return;
    }
    act = _raiz;
    bool menor = false;
    Nodo* hijo;
    while (act != nullptr){
        menor = clave < act->valor;
        hijo = new Nodo(clave, act);
        act = menor ? act->izq : act->der;
        if (act != nullptr){delete hijo;}
    }
    if (menor){
        hijo->padre->izq = new Nodo(clave, hijo->padre);
    } else{
        hijo->padre->der = new Nodo(clave, hijo->padre);
    }
    delete hijo;
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    bool menor = false;
    Nodo* padre = nullptr;
    Nodo* act = _raiz;
    //guardo el padre para modificar directamente la estructura
    while (act != nullptr && act->valor != clave){
        padre = act;
        menor = clave < act->valor;
        act = menor ? act->izq : act->der;
    }

    if (act->valor != clave){ return; }//no esta el nodo que se quiere eliminar

    if (act->izq == nullptr && act->der == nullptr){
        if (act == _raiz){
            //no tiene hijos y es hoja, chau raiz, chau arbol
            _raiz = nullptr;
        } else{
            if (menor){
                padre->izq = nullptr;
            } else{
                padre->der = nullptr;
            }
        }
        delete act;
    } else{
        if (act->izq != nullptr && act->der != nullptr){
            //caso dos hijos

            //sube el valor minimo del subabrbol derecho a la posicion del nodo eliminado
            T min = _minimo(act->der);
            remover(min);
            act->valor = min;
        } else{
            //caso un solo hijo
            Nodo* hijo = (act->izq != nullptr) ? act->izq : act->der;

            if (act == _raiz){
                _raiz = hijo;
            } else{
                if (menor){
                    padre->izq = hijo;
                } else{
                    padre->der = hijo;
                }
            }
            delete act;
        }
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    _siguiente = nullptr;
    Nodo* nodo = _raiz;
    _inorder_tree_walk_search_next(nodo, clave);
    return *_siguiente;

}

template <class T>
void Conjunto<T>::_inorder_tree_walk_search_next(Nodo* nodo, const T& clave) {
    //de Cormen
    if(nodo != nullptr){
        _inorder_tree_walk_search_next(nodo->izq, clave);
        if(_siguiente == nullptr && (nodo->valor > clave)){
            _siguiente = new T(nodo->valor);
            return;
        }
        _inorder_tree_walk_search_next(nodo->der, clave);
    }
}

template <class T>
const T& Conjunto<T>::minimo() const {
    return _minimo(_raiz);
}

template <class T>
T& Conjunto<T>::_minimo(Nodo* actual) const {
    while (actual->izq != nullptr){
        actual = actual->izq;
    }
    return actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    return this->_maximo(_raiz);
}

template <class T>
T& Conjunto<T>::_maximo(Conjunto::Nodo* act) const {
    while (act->der != nullptr){
        act = act->der;
    }
    return act->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    int res = _cardinal(0, _raiz);
    return res;
}

template <class T>
int Conjunto<T>::_cardinal(int count, Nodo* act) const {
    if (act == nullptr)
        return 0;

    return count + _cardinal(count, act->izq) + _cardinal(count, act->der) + 1;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

