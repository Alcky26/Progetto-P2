#include "spesa.h"

spesa::spesa(QString titolo, QString descrizione) : elenco(titolo,descrizione), _spesa()
{

}

spesa::spesa(QString titolo, QString descrizione, const lista<spese> &spesa) : elenco(titolo,descrizione)
{
    for(lista<spese>::constiterator ci = spesa.begin(); ci!=spesa.end();ci++)
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
    for(lista<spese>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        total+= ci->costo;
    }
    return total;
}

double spesa::CostoRimanente() const
{
    double total=0;
    for(lista<spese>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        if(!(ci->isDone))
        {
            total+= ci->costo;
        }

    }
    return total;
}

double spesa::CostoAttuale() const
{
    double total=0;
    for(lista<spese>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        if(ci->isDone)
        {
            total+= ci->costo;
        }

    }
    return total;
}

void spesa::addElemento(const QString &elemento, const double &prezzo)
{
    spese newElement;
    newElement.costo=prezzo;
    newElement.value=elemento;
    _spesa.insertBack(newElement);
}

void spesa::addElemento(const spese &value)
{
    _spesa.insertBack(value);
}

