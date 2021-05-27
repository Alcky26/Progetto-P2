#include "ricorrenza.h"


ricorrenza::ricorrenza(QString titolo, QString corpo, QDate date, QTime time, Tipo type) : annotazione(titolo), nota(titolo,corpo), _date(date), _time(time), _type(type)
{

}

ricorrenza::~ricorrenza()
{

}

Tipo ricorrenza::getType() const
{
    return _type;
}

void ricorrenza::setType(const Tipo &type)
{
    _type = type;
}

QDate ricorrenza::getDate() const
{
    return _date;
}

void ricorrenza::setDate(const QDate &date)
{
    _date = date;
}

QTime ricorrenza::getTime() const
{
    return _time;
}

void ricorrenza::setTime(const QTime &time)
{
    _time = time;
}

QStringList ricorrenza::getTipi()
{
    QStringList tipologieItems;
    tipologieItems.push_back("Giornaliero");
    tipologieItems.push_back("Settimanale");
    tipologieItems.push_back("Mensile");
    tipologieItems.push_back("Annuale");
    return tipologieItems;
}

bool ricorrenza::operator==(const ricorrenza &r) const
{
    return getTitolo()== r.getTitolo() &&
           getCorpo() == r.getCorpo() &&
           _date == r.getDate() &&
           _time == r.getTime() &&
           _type == r.getType() ;
}

bool ricorrenza::operator!=(const ricorrenza &r) const
{
    return !operator==(r);
}

QString ricorrenza::typeToQString() const
{
    if( _type == Giornaliero)
    {
        return "Giornaliero";
    }
    else if( _type == Settimanale)
    {
        return "Settimanale";
    }
    else if( _type == Mensile)
    {
        return "Mensile";
    }
    else if( _type == Annuale)
    {
        return "Annuale";
    }
    else return "null";
}

Tipo ricorrenza::QStringToTipo(QString stringa) const
{
    if( stringa == "Giornaliero")
    {
        return Giornaliero;
    }
    else if( stringa == "Settimanale")
    {
        return Settimanale;
    }
    else if( stringa == "Mensile")
    {
        return Mensile;
    }
    else
    {
        return Annuale;
    }
}
/*
void ricorrenza::operator+(const QString &value)
{
   setCorpo(getCorpo() + " " + value);
}
*/


void ricorrenza::Aggiorna()
{
    if( _type == Giornaliero)
    {
        setDate(getDate().addDays(1));
    }
    else if( _type == Settimanale)
    {
        setDate(getDate().addDays(7));
    }
    else if( _type == Mensile)
    {
        setDate(getDate().addMonths(1));
    }
    else if( _type == Annuale)
    {
        setDate(getDate().addYears(1));
    }
}

void ricorrenza::Posticipa()
{
    setTime(getTime().addSecs(600));
}
