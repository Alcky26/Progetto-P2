#include "metodi_extra.h"

Tipo metodi_extra::MetodoSupporto(int _index)
{
    Tipo _nuovoTipo=Giornaliero;

    if(_index==0)
        _nuovoTipo = Giornaliero;
    else if (_index == 1)
        _nuovoTipo = Settimanale;
    else if (_index == 2)
       _nuovoTipo = Mensile;
    else if (_index == 3)
       _nuovoTipo = Annuale;

    return _nuovoTipo;
}

QString metodi_extra::ElencoAsText(lista<type_elenco *> _elenco)
{
    QString _finalValue="";
    for( lista<type_elenco*>::constiterator ci = _elenco.begin(); ci!=_elenco.end();ci++)
    {
        _finalValue += (*ci)->getValue();
        if( (*ci)->getIsDone())
            _finalValue += "    Effettuato ";
        else
            _finalValue += "    Non Effettuato ";
        _finalValue+="\n";
    }
    return _finalValue;
}

QString metodi_extra::SpesaAsText(lista<type_spesa *> _spesa)
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
