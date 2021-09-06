#ifndef NODO_H
#define NODO_H

template<class T>
class lista;

template<class T>
class nodo
{
    friend class lista<T>;
private:
    T _info;
    nodo *_prev, *_next; // double Linked
    // Costruttore
    nodo();
    nodo(const T& t, nodo *prev=nullptr, nodo *next=nullptr);
    // Distruttore
    ~nodo();
    // Get
    T getInfo() const;
};

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

#endif //NODO_H
