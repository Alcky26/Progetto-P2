#include "nodo.h"

template<class T>
nodo<T>::nodo():_next(nullptr), _prev(nullptr) {}

template<class T>
nodo<T>::nodo(const T &t, nodo *prev, nodo *next):_info(t), _prev(prev), _next(next) {}

template<class T>
nodo<T>::~nodo()
{
    delete _next;
}

template<class T>
T nodo<T>::getInfo() const
{
    return _info;
}
