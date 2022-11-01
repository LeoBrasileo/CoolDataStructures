
template <class T>
Set<T>::Set() : _root(nullptr), _next(nullptr) {}

template <class T>
Set<T>::~Set() {
    recursiveDestruction(_root);
}

template <class T>
void Set<T>::recursiveDestruction(Node* actual) {
    if (actual != nullptr){
        recursiveDestruction(actual->leftNode);
        recursiveDestruction(actual->rightNode);
        delete actual;
    }
}

template <class T>
bool Set<T>::in(const T& clave) const {
    bool menor = false;
    Node* act = _root;
    while (act != nullptr){
        if (act->value == clave){
            return true;
        }
        menor = clave < act->value;
        act = menor ? act->leftNode : act->rightNode;
    }
    return false;
}

template <class T>
void Set<T>::insert(const T& clave) {
    Node* act;
    if (_root == nullptr){
        _root = new Node(clave, nullptr);
        return;
    }
    act = _root;
    bool menor = false;
    Node* hijo;
    while (act != nullptr){
        if (act->value == clave){ return;}
        menor = clave < act->value;
        hijo = new Node(clave, act);
        act = menor ? act->leftNode : act->rightNode;
        if (act != nullptr){delete hijo;}
    }
    if (menor){
        hijo->parent->leftNode = new Node(clave, hijo->parent);
    } else{
        hijo->parent->rightNode = new Node(clave, hijo->parent);
    }
    delete hijo;
}

template <class T>
void Set<T>::remove(const T& clave) {
    bool menor = false;
    Node* padre = nullptr;
    Node* act = _root;
    //guardo el parent para modificar directamente la estructura
    while (act != nullptr && act->value != clave){
        padre = act;
        menor = clave < act->value;
        act = menor ? act->leftNode : act->rightNode;
    }

    if (act->value != clave){ return; }//no esta el nodo que se quiere eliminar

    if (act->leftNode == nullptr && act->rightNode == nullptr){
        if (act == _root){
            //no tiene hijos y es hoja, chau raiz, chau arbol
            _root = nullptr;
        } else{
            if (menor){
                padre->leftNode = nullptr;
            } else{
                padre->rightNode = nullptr;
            }
        }
        delete act;
    } else{
        if (act->leftNode != nullptr && act->rightNode != nullptr){
            //caso dos hijos

            //sube el value min del subabrbol derecho a la posicion del nodo eliminado
            T min = _min(act->rightNode);
            remove(min);
            act->value = min;
        } else{
            //caso un solo hijo
            Node* hijo = (act->leftNode != nullptr) ? act->leftNode : act->rightNode;

            if (act == _root){
                _root = hijo;
            } else{
                if (menor){
                    padre->leftNode = hijo;
                } else{
                    padre->rightNode = hijo;
                }
            }
            delete act;
        }
    }
}

template <class T>
const T& Set<T>::next(const T& clave) {
    _next = nullptr;
    _inorder_tree_walk_search_next(_root, clave);
    return *_next;
    delete _next;

}

template <class T>
void Set<T>::_inorder_tree_walk_search_next(Node* nodo, const T& clave) {
    //de Cormen's
    if(nodo != nullptr){
        _inorder_tree_walk_search_next(nodo->leftNode, clave);
        if(_next == nullptr && (nodo->value > clave)){
            _next = &nodo->value;
            return;
        }
        _inorder_tree_walk_search_next(nodo->rightNode, clave);
    }
}

template <class T>
const T& Set<T>::min() const {
    return _min(_root);
}

template <class T>
T& Set<T>::_min(Node* actual) const {
    while (actual->leftNode != nullptr){
        actual = actual->leftNode;
    }
    return actual->value;
}

template <class T>
const T& Set<T>::max() const {
    return this->_max(_root);
}

template <class T>
T& Set<T>::_max(Set::Node* act) const {
    while (act->rightNode != nullptr){
        act = act->rightNode;
    }
    return act->value;
}

template <class T>
unsigned int Set<T>::cardinal() const {
    int res = _cardinal(0, _root);
    return res;
}

template <class T>
int Set<T>::_cardinal(int count, Node* act) const {
    if (act == nullptr)
        return 0;

    return count + _cardinal(count, act->leftNode) + _cardinal(count, act->rightNode) + 1;
}

template <class T>
void Set<T>::show(std::ostream&) const {
    assert(false);
}

