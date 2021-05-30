#include "promemoria.h"


promemoria::promemoria(QString titolo, QString corpo, QDate date, QTime time) : annotazione(titolo), nota(titolo,corpo), _date(date), _time(time)
{

}

promemoria::promemoria(QDomElement prom):
    annotazione(prom.childNodes().at(0).toElement().childNodes().at(0).toElement()),
    nota(prom.childNodes().at(0).toElement()),
    _date(strToItaDate(prom.attribute("Data"))),
    _time(prom.attribute("Ora").split(":")[0].toInt(),prom.attribute("Ora").split(":")[1].toInt(),prom.attribute("Ora").split(":")[2].toInt())
{

}

promemoria::~promemoria()
{

}

QDate promemoria::strToItaDate(const QString& date)
{
    return QDate::fromString(date,"dd/MM/yyyy");
}

QString promemoria::dateToItaStr(const QDate& date)
{
    return date.toString("dd/MM/yyyy");
}

QDomElement promemoria::XmlSerialize(QDomDocument doc) const
{
    QDomElement prom = doc.createElement("Promemoria");
    prom.appendChild(nota::XmlSerialize(doc));
    prom.setAttribute("Data", dateToItaStr(_date));
    prom.setAttribute("Ora", _time.toString());
    return prom;
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
