#include "spesa.h"

spesa::spesa() : elenco(), _spesa()
{

}

spesa::spesa(QString titolo, QString descrizione) : annotazione(titolo),elenco(titolo,descrizione), _spesa()
{

}

spesa::spesa(QString titolo, QString descrizione, const lista<type_spesa*> &spesa) : annotazione(titolo),elenco(titolo,descrizione)
{
    for(lista<type_spesa*>::constiterator ci = spesa.begin(); ci!=spesa.end();ci++)
    {
        _spesa.insertFront(*ci);
    }
}

spesa::~spesa()
{
    _spesa.clear();
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
        temp = (*ci)->getValue() + " : " +  QString::number((*ci)->getCost()) + "\n";
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




