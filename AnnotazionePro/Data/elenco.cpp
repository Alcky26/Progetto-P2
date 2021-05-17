#include "elenco.h"

elenco::elenco() : annotazione(), _elenco()
{

}

elenco::elenco(QString titolo, QString descrizione):annotazione(titolo),_descrizione(descrizione),_elenco()
{

}

elenco::~elenco()
{

}

elenco::elenco(QString titolo, QString descrizione, lista<QString*> &elenco):annotazione(titolo),_descrizione(descrizione)
{
    /*type_elenco* elem=new type_elenco();
    for( lista<QString*>::constiterator ci = elenco.begin(); ci!=elenco.end(); ci++)
    {
        elem->setValue(*ci);
        _elenco.insertFront(elem);
    }*/

    type_elenco* newElement;

    for( lista<QString*>::constiterator ci = elenco.begin(); ci!=elenco.end();ci++)
    {
        newElement= new type_elenco(*ci);
        _elenco.insertFront(newElement);
    }
}

QString elenco::descrizione() const
{
    return _descrizione;
}

void elenco::setDescrizione(const QString &descrizione)
{
    _descrizione = descrizione;
}

void elenco::addElemento(const QString* &elemento)
{
    type_elenco* elem = new type_elenco();
    elem->setValue(*elemento);
    _elenco.insertBack(elem);
}
