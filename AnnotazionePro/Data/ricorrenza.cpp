#include "ricorrenza.h"


ricorrenza::ricorrenza(QString titolo, QString corpo, QDate date, QTime time, Tipo type) : annotazione(titolo), nota(titolo,corpo), _date(date), _time(time), _type(type)
{

}

ricorrenza::ricorrenza(QDomElement ric):
    annotazione(ric.childNodes().at(0).toElement().childNodes().at(0).toElement()),
    nota(ric.childNodes().at(0).toElement()),
    _date(metodi_extra::strToItaDate(ric.attribute("Data"))),
    _time(ric.attribute("Ora").split(":")[0].toInt(),ric.attribute("Ora").split(":")[1].toInt(),ric.attribute("Ora").split(":")[2].toInt()),
    _type(metodi_extra::QStringToTipo(ric.attribute("Tipo")))
{

}

ricorrenza::~ricorrenza()
{

}

QDomElement ricorrenza::XmlSerialize(QDomDocument doc) const
{
    QDomElement ricor = doc.createElement("Ricorrenza");
    ricor.appendChild(nota::XmlSerialize(doc));
    ricor.setAttribute("Data", _date.toString());
    ricor.setAttribute("Ora", _time.toString());
    ricor.setAttribute("Tipo", metodi_extra::TipoToQString(getType()));
    return ricor;
}

QString ricorrenza::ToString() const
{
    QString testo;
    testo+=nota::ToString();
    return testo+"Data: "+getDate().toString()+";Time: "+getTime().toString()+";Tipo: "+metodi_extra::TipoToQString(getType())+";";
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






