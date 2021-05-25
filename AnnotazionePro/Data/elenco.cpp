#include "elenco.h"

elenco::elenco() : annotazione()
{

}

elenco::elenco(QString titolo, QString descrizione):annotazione(titolo),_descrizione(descrizione),_elenco()
{
    //_elenco = new lista<type_elenco*>();
}

elenco::~elenco()
{

}

QString elenco::getListAsText()
{
    QString _finalValue="";
    for( lista<type_elenco*>::constiterator ci = _elenco.begin(); ci!=_elenco.end();ci++)
    {
        _finalValue += (*ci)->getValue();
        _finalValue+="\n";
    }
    return _finalValue;
}

elenco::elenco(QString titolo, QString descrizione, lista<QString*> &elenco):annotazione(titolo),_descrizione(descrizione)
{
    type_elenco* newElement;

    for( lista<QString*>::constiterator ci = elenco.begin(); ci!=elenco.end();ci++)
    {
        newElement= new type_elenco(*ci);
        _elenco.insertFront(newElement);
    }
}

elenco::elenco(QString titolo, QString descrizione, lista<type_elenco*> elenco):annotazione(titolo),_descrizione(descrizione)
{
    //_elenco = new lista<type_elenco*>();
    for( lista<type_elenco*>::constiterator ci = elenco.begin(); ci!=elenco.end();ci++)
    {
        _elenco.insertFront(*ci);
    }
}

QString elenco::getDescrizione() const
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

lista<type_elenco *> elenco::getElenco() const
{
    return _elenco;
}

