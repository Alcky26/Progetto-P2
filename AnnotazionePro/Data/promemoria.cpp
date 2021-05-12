#include "promemoria.h"


promemoria::promemoria(QString titolo, QString corpo, QDate date, QTime time) : annotazione(titolo), nota(titolo,corpo), _date(date), _time(time)
{

}

promemoria::~promemoria()
{

}

QDate promemoria::getDate() const
{
    return _date;
}

void promemoria::setDate(const QDate &Date)
{
    _date = Date;
}

QTime promemoria::getTime() const
{
    return _time;
}

void promemoria::setTime(const QTime &time)
{
    _time = time;
}


bool promemoria::operator==(const promemoria &p) const
{
    return getTitolo()== p.getTitolo() &&
           getCorpo() == p.getCorpo() &&
           _date == p.getDate() &&
           _time == p.getTime();
}

bool promemoria::operator!=(const promemoria &p) const
{
    return !operator==(p);
}
/*
void promemoria::operator+(const QString &value)
{
    setCorpo(getCorpo() + " " + value);
}
*/
