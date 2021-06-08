#include "promemoria.h"


promemoria::promemoria(QString titolo, QString corpo, QDate date, QTime time) : annotazione(titolo), nota(titolo,corpo), _date(date), _time(time)
{

}

promemoria::promemoria(QDomElement prom):
    annotazione(prom.childNodes().at(0).toElement().childNodes().at(0).toElement()),
    nota(prom.childNodes().at(0).toElement()),
    _date(metodi_extra::strToItaDate(prom.attribute("Data"))),
    _time(prom.attribute("Ora").split(":")[0].toInt(),prom.attribute("Ora").split(":")[1].toInt(),prom.attribute("Ora").split(":")[2].toInt())
{

}

promemoria::~promemoria()
{

}

QDomElement promemoria::XmlSerialize(QDomDocument doc) const
{
    QDomElement prom = doc.createElement("Promemoria");
    prom.appendChild(nota::XmlSerialize(doc));
    prom.setAttribute("Data", metodi_extra::dateToItaStr(_date));
    prom.setAttribute("Ora", _time.toString());
    return prom;
}

QString promemoria::ToString() const
{
    QString testo;
    testo+=nota::ToString();
    return testo+"Data: "+getDate().toString()+"; Time: "+getTime().toString()+"; ";
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
