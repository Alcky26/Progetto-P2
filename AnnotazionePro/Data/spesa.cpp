#include "spesa.h"

spesa::spesa() : elenco(), _spesa()
{

}

spesa::spesa(QString titolo, QString descrizione) : annotazione(titolo),elenco(titolo,descrizione), _spesa()
{

}

spesa::spesa(QString titolo, QString descrizione, const lista<type_spesa*> &spesa) : annotazione(titolo),elenco(titolo,descrizione),_spesa(spesa)
{

}

spesa::spesa(QDomElement spesa):
    annotazione(spesa.childNodes().at(0).toElement().childNodes().at(0).toElement()),
    elenco(spesa.childNodes().at(0).toElement())
{
    int count=1;
    type_spesa *ts;
    while(spesa.childNodes().at(count).isElement())
    {
        ts=new type_spesa();
        ts->setValue(spesa.childNodes().at(count).toElement().attribute("Value"));
        ts->setIsDone(spesa.childNodes().at(count).toElement().attribute("IsDone")=="0" ? 0:1);
        ts->setCost(spesa.childNodes().at(count).toElement().attribute("Cost").toDouble());
        _spesa.insertBack(ts);
        count++;
    }
}

spesa::spesa(const spesa &spes):annotazione(spes.getTitolo()),elenco(spes.getTitolo(),spes.getDescrizione()),_spesa(spes.getSpesa())
{

}

spesa::~spesa()
{
    _spesa.clear();
}

QDomElement spesa::XmlSerialize(QDomDocument doc) const
{
    QDomElement spesa = doc.createElement("Spesa");
    spesa.appendChild(elenco::XmlSerialize(doc));
    for( lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        QDomElement elemento= doc.createElement("Elemento");
        elemento.setAttribute("Value",(*ci)->getValue());
        elemento.setAttribute("IsDone",(*ci)->getIsDone());
        elemento.setAttribute("Cost",(*ci)->getCost());
        spesa.appendChild(elemento);
    }
    return spesa;
}

QString spesa::ToString() const
{
    QString testo;
    testo+=annotazione::ToString();
    testo+="Descrizione: "+getDescrizione()+";";
    for( lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        testo+="Valore: "+(*ci)->getValue()+";Costo: "+QString::number((*ci)->getCost())+";"+((*ci)->getIsDone() ? "0" : "1" )+";";
    }
    return testo;
}

double spesa::CostoComplessivo() const
{

    double total=0;
    for(lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        total+= (*ci)->getCost();
    }
    return total;
}

void spesa::addElement(const QString &elemento, const double &prezzo)
{
    type_spesa* newElement = new type_spesa();
    newElement->setCost(prezzo);
    newElement->setValue(elemento);
    _spesa.insertBack(newElement);
}

void spesa::addElement(const type_spesa* &value)
{

    //_spesa.insertBack(value);
}

void spesa::Remove(const type_spesa* &_this)
{
    for(lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        if((*ci)->getCost()==_this->getCost() && (*ci)->getValue()==_this->getValue() && (*ci)->getIsDone() == _this->getIsDone())
        {
            _spesa.erase(ci);
        }
    }
}

lista<type_spesa *> spesa::getSpesa() const
{
    return _spesa;
}

void spesa::setSpesa(lista<type_spesa *> _newSpesa)
{
    _spesa.clear();
    for( lista<type_spesa*>::constiterator ci = _newSpesa.begin(); ci!=_newSpesa.end();ci++)
    {
        _spesa.insertFront(*ci);
    }
}




