#include "metodi_extra.h"

ricorrenza::Tipo metodi_extra::IntToTipo(int _index)
{
    ricorrenza::Tipo _nuovoTipo=ricorrenza::Giornaliero;

    if(_index==0)
        _nuovoTipo = ricorrenza::Giornaliero;
    else if (_index == 1)
        _nuovoTipo = ricorrenza::Settimanale;
    else if (_index == 2)
       _nuovoTipo = ricorrenza::Mensile;
    else if (_index == 3)
       _nuovoTipo = ricorrenza::Annuale;

    return _nuovoTipo;
}

ricorrenza::Tipo metodi_extra::QStringToTipo(QString stringa)
{
    if( stringa == "Giornaliero")
    {
        return ricorrenza::Giornaliero;
    }
    else if( stringa == "Settimanale")
    {
        return ricorrenza::Settimanale;
    }
    else if( stringa == "Mensile")
    {
        return ricorrenza::Mensile;
    }
    else
    {
        return ricorrenza::Annuale;
    }
}

QString metodi_extra::TipoToQString(ricorrenza::Tipo _type)
{
    if( _type == ricorrenza::Giornaliero)
    {
        return "Giornaliero";
    }
    else if( _type == ricorrenza::Settimanale)
    {
        return "Settimanale";
    }
    else if( _type == ricorrenza::Mensile)
    {
        return "Mensile";
    }
    else if( _type == ricorrenza::Annuale)
    {
        return "Annuale";
    }
    else return "null";
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

QDate metodi_extra::strToItaDate(const QString& date)
{
    return QDate::fromString(date,"dd/MM/yyyy");
}

QString metodi_extra::dateToItaStr(const QDate& date)
{
    return date.toString("dd/MM/yyyy");
}

QStringList metodi_extra::getTipi()
{
    QStringList tipologieItems;
    tipologieItems.push_back("Giornaliero");
    tipologieItems.push_back("Settimanale");
    tipologieItems.push_back("Mensile");
    tipologieItems.push_back("Annuale");
    return tipologieItems;
}
