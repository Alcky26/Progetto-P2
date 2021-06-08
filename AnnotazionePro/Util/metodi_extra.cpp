#include "metodi_extra.h"

QString metodi_extra::ElencoAsText(const lista<type_elenco *> _elenco)
{
    QString _finalValue="";
    for( lista<type_elenco*>::constiterator ci = _elenco.begin(); ci!=_elenco.end();ci++)
    {
        _finalValue += (*ci)->getValue();
        if( (*ci)->getIsDone())
            _finalValue += " : ✔ ";
        else
            _finalValue += " : ✘ ";
        _finalValue+="\n";
    }
    return _finalValue;
}

QString metodi_extra::SpesaAsText(const lista<type_spesa *> _spesa)
{
    QString _finalValue="";
    QString temp;
    for( lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        temp = (*ci)->getValue() + " : " +  QString::number((*ci)->getCost()) + " : ";
        if((*ci)->getIsDone())
            temp += "✔ \n";
        else
            temp += "✘ \n";
        _finalValue+= temp;
    }
    return _finalValue;
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

QString metodi_extra::dateToItaStr(const QDate &date)
{
     return date.toString("dd/MM/yyyy");
}

QDate metodi_extra::strToItaDate(const QString &date)
{
    return QDate::fromString(date,"dd/MM/yyyy");
}
