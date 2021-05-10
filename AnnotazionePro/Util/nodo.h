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
    nodo *_prev, *_next;
    nodo();
    nodo(const T& t, nodo *prev=nullptr, nodo *next=nullptr);
    ~nodo();
    T getInfo() const;
};

#endif //NODO_H
