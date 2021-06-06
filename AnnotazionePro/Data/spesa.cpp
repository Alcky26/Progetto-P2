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
        _spesa.insertFront(ts);
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

double spesa::CostoComplessivo() const
{

    double total=0;
    for(lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        total+= (*ci)->getCost();//(ci)*.getCost();
    }
    return total;
}

double spesa::CostoRimanente() const
{
    double total=0;
    for(lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        if(!(*ci)->getIsDone())
        {
            total+= (*ci)->getCost();
        }

    }
    return total;
}

double spesa::CostoAttuale() const
{
    double total=0;
    for(lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        if((*ci)->getIsDone())
        {
            total+= (*ci)->getCost();
        }

    }
    return total;
}

QString spesa::getListSpesaAsText()
{
    QString _finalValue="";
    QString temp;
    for( lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        temp = (*ci)->getValue() + " : " +  QString::number((*ci)->getCost()) + " : ";
        if((*ci)->getIsDone())
            temp += "Effettuato \n";
        else
            temp += "Non Effettuato \n";
        _finalValue+= temp;
    }
    return _finalValue;

}

void spesa::addElement(const QString &elemento, const double &prezzo)
{
    type_spesa* newElement = new type_spesa();
    newElement->setCost(prezzo);
    newElement->setValue(elemento);
    _spesa.insertBack(newElement);
}

void spesa::addElement( type_spesa* const &value)
{
    _spesa.insertBack(value);
}

void spesa::Remove(const QString &elemento, const double &prezzo)
{
    for(lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        if((*ci)->getCost()==prezzo && (*ci)->getValue()==elemento)
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




