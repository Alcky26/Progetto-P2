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
        _spesa.insertBack(*ci);
    }
}

spesa::~spesa()
{

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
    for( lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        qDebug() << (*ci)->getCost();
        if( (*ci)->getCost() == 0 )
            _finalValue = _finalValue + (*ci)->getValue() + " : 0 \n";
        else
            _finalValue = _finalValue + (*ci)->getValue() + " : " +  QString::number((*ci)->getCost()) + "\n";
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




