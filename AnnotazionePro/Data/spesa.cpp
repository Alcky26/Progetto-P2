#include "spesa.h"

spesa::spesa() : elenco(), _spesa()
{

}

spesa::spesa(QString titolo, QString descrizione) : elenco(titolo,descrizione), _spesa()
{

}

spesa::spesa(QString titolo, QString descrizione, const lista<type_spesa> &spesa) : elenco(titolo,descrizione)
{
    for(lista<type_spesa>::constiterator ci = spesa.begin(); ci!=spesa.end();ci++)
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
    for(lista<type_spesa>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        total+= ci->getCost();
    }
    return total;
}

double spesa::CostoRimanente() const
{
    double total=0;
    for(lista<type_spesa>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        if(!ci->getIsDone())
        {
            total+= ci->getCost();
        }

    }
    return total;
}

double spesa::CostoAttuale() const
{
    double total=0;
    for(lista<type_spesa>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        if(ci->getIsDone())
        {
            total+= ci->getCost();
        }

    }
    return total;
}

void spesa::addElement(const QString &elemento, const double &prezzo)
{
    type_spesa newElement;
    newElement.setCost(prezzo);
    newElement.setValue(elemento);
    _spesa.insertBack(newElement);
}

void spesa::addElement(const type_spesa &value)
{
    _spesa.insertBack(value);
}

void spesa::Remove(const QString &elemento, const double &prezzo)
{
    for(lista<type_spesa>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        if(ci->getCost()==prezzo && ci->getValue()==elemento)
        {
            _spesa.erase(ci);
        }
    }
}




