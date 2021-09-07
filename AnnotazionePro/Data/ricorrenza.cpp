#include "ricorrenza.h"


ricorrenza::ricorrenza(QString titolo, QString corpo, QDate date, QTime time, Tipo type)
    : annotazione(titolo), nota(titolo,corpo), _date(date), _time(time), _type(type)
{

}

ricorrenza::ricorrenza(QDomElement ric):
    annotazione(ric.childNodes().at(0).toElement().childNodes().at(0).toElement()),
    nota(ric.childNodes().at(0).toElement()),
    _date(metodi_extra::strToItaDate(ric.attribute("Data"))),
    _time(ric.attribute("Ora").split(":")[0].toInt(),ric.attribute("Ora").split(":")[1].toInt(),ric.attribute("Ora").split(":")[2].toInt()),
    _type(QStringToTipo(ric.attribute("Tipo")))
{    
}

ricorrenza::~ricorrenza()
{

}

bool ricorrenza::operator==(const ricorrenza &R) const {
    return R.getDate()==_date && R.getTime()==_time && R.getType()==_type && nota::operator==(R);
}

bool ricorrenza::operator!=(const ricorrenza &R) const
{
    return !(this==&R);
}

ricorrenza &ricorrenza::operator=(const ricorrenza &R)
{
    if(this!=&R)
    {
        _date=R.getDate();
        _time=R.getTime();
        _type=R.getType();
        nota::operator==(R);
    }
    return *this;
}

QDomElement ricorrenza::XmlSerialize(QDomDocument doc) const
{
    QDomElement ricor = doc.createElement("Ricorrenza");
    ricor.appendChild(nota::XmlSerialize(doc));
    ricor.setAttribute("Data", metodi_extra::dateToItaStr(_date));
    ricor.setAttribute("Ora", _time.toString()); 
    ricor.setAttribute("Tipo", TipoToQString());
    return ricor;
}

QString ricorrenza::ToString() const
{
    QString testo;
    testo+=nota::ToString();
    return testo+"Data: "+getDate().toString()+"; Time: "+getTime().toString()+"; Tipo: "+TipoToQString()+"; ";
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

QString ricorrenza::TipoToQString() const
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
    else if( stringa == "Annuale")
    {
        return Annuale;
    }
    else
        return Giornaliero;
}






