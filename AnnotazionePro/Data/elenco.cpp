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

elenco::elenco(QString titolo, QString descrizione, const lista<QString> &elenco):annotazione(titolo),_descrizione(descrizione)
{
    type_elenco elem;
    for( lista<QString>::constiterator ci = elenco.begin(); ci!=elenco.end(); ci++)
    {
        elem.setValue(*ci);
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
    type_elenco elem;
    elem.setValue(elemento);
    _elenco.insertBack(elem);

}
