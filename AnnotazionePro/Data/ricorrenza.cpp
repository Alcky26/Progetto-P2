#include "ricorrenza.h"


ricorrenza::ricorrenza(QString titolo, QString descrizione, QString corpo, QDate date, QTime time, Tipo type) : Annotazione(titolo,descrizione), Nota(titolo,descrizione,corpo), _date(date), _time(time), _type(type)
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

bool ricorrenza::operator==(const ricorrenza &r) const
{
    return getTitolo()== r.getTitolo() &&
           getDescrizione()== r.getDescrizione() &&
           getCorpo() == r.getCorpo() &&
           _date == r.getDate() &&
           _time == r.getTime() &&
           _type == r.getType() ;
}

bool ricorrenza::operator!=(const ricorrenza &r) const
{
    return !operator==(r);
}

void ricorrenza::operator+(const QString &value)
{
   setCorpo(getCorpo() + " " + value);
}
