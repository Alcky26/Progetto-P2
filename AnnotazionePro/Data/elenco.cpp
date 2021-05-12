#include "elenco.h"

elenco::elenco(QString titolo, QString descrizione):annotazione(titolo),_descrizione(descrizione),_elenco()
{

}

elenco::~elenco()
{

}

elenco::elenco(QString titolo, QString descrizione, const lista<QString> &elenco):annotazione(titolo),_descrizione(descrizione)
{
    elenchi elem;
    for( lista<QString>::constiterator ci = elenco.begin(); ci!=elenco.end(); ci++)
    {
        elem.value=(*ci);
        _elenco.insertFront(elem);
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

void elenco::addElemento(const QString &elemento)
{
    elenchi elem;
    elem.value=elemento;
    _elenco.insertBack(elem);

}
