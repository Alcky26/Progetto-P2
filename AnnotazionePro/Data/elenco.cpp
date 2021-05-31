#include "elenco.h"

elenco::elenco() : annotazione()
{

}
elenco::elenco(QString titolo, QString descrizione):annotazione(titolo),_descrizione(descrizione),_elenco()
{
    //_elenco = new lista<type_elenco*>();
}

elenco::elenco(QDomElement elen):
    annotazione(elen.childNodes().at(0).toElement()),
    _descrizione(elen.attribute("Descrizione"))
{
    int count=1;
    type_elenco *te=new type_elenco();
    while(elen.childNodes().at(count).isElement())
    {
        te->setValue(elen.childNodes().at(count).toElement().attribute("Value"));
        te->setIsDone(elen.childNodes().at(count).toElement().attribute("IsDone")=="0" ? 0:1);
        _elenco.insertFront(te);
        count++;
    }
    delete te;
}

elenco::~elenco()
{
    _elenco.clear();
}

QDomElement elenco::XmlSerialize(QDomDocument doc) const
{
    QDomElement elenco = doc.createElement("Elenco");
    elenco.appendChild(annotazione::XmlSerialize(doc));
    elenco.setAttribute("Descrizione", _descrizione);

    for( lista<type_elenco*>::constiterator ci = _elenco.begin(); ci!=_elenco.end();ci++)
    {
        QDomElement elemento=doc.createElement("Elemento");
        elemento.setAttribute("Value",(*ci)->getValue());
        elemento.setAttribute("IsDone",(*ci)->getIsDone());
        elenco.appendChild(elemento);
    }
    return elenco;
}

QString elenco::getListAsText()
{
    QString _finalValue="";
    for( lista<type_elenco*>::constiterator ci = _elenco.begin(); ci!=_elenco.end();ci++)
    {
        _finalValue += (*ci)->getValue();
        if( (*ci)->getIsDone())
            _finalValue += "    Confermato ";
        else
            _finalValue += "    Non Confermato ";
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

void elenco::setElenco(lista<type_elenco *> _newElenco)
{
    _elenco.clear();
    for( lista<type_elenco*>::constiterator ci = _newElenco.begin(); ci!=_newElenco.end();ci++)
    {
        _elenco.insertFront(*ci);
    }
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

