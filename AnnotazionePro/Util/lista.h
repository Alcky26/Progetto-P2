#ifndef LISTA_H
#define LISTA_H

#include "nodo.h"

template <class T>
class lista
{
private:
    nodo<T> *_first, *_end;//_end punta all'ultimo nodo, non alla "cella" successiva
    static nodo<T> *copia(nodo<T>* f, nodo<T>*& l); //per copia profonda
    unsigned int _size; //dimensione della lista

public:
    lista();
    lista(const lista& l);
    ~lista();
    lista& operator=(const lista& d);
    unsigned int getSize() const;
    bool isEmpty() const;
    void insertFront(const T& t);
    void insertBack(const T& t);
    class constiterator {
        friend class lista<T>;
        private:
            nodo<T> *_ptr;
            bool _pastTheEnd; // true sse constiterator è "past-the-end"
            constiterator(nodo<T>* p, bool pte=false);
        public:
            constiterator();

            const T& operator*() const;
            const T* operator->() const;
            constiterator& operator++();
            constiterator operator++(int);
            constiterator& operator--();
            constiterator operator--(int);
            bool operator==(const constiterator& x) const;
            bool operator!=(const constiterator& x) const;
        };
    //restituisce il constiterator al primo nodo della lista
    constiterator begin() const;

    //restituisce il constiterator al pte
    constiterator end() const;

    //restituisce un reference al primo elemento della lista
    T& front();
    const T& front() const;

    //restituisce un reference all'ultimo elemento della lista
    T& back();
    const T& back() const;

    //rimuove dalla lista un singolo elemento dato un constiterator
    constiterator erase(constiterator x);

    //rimuove dalla lista tutti gli elementi uguali a t
    void remove(const T& t);

    //indica se la lista contiene l'elemento t
    bool contains(const T& t) const;

    //resituisce il constiterator dell'elemento dato t
    constiterator indexOf(const T& t) const;

    //rimuove tutti gli elementi della lista
    void clear();
};

#endif // LISTA_H

