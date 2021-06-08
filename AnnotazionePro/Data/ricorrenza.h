#ifndef RICORRENZA_H
#define RICORRENZA_H

#include "nota.h"
#include <QDate>
#include <QTime>
#include <QDomDocument>
#include <QDomElement>
#include "Util/metodi_extra.h"

enum Tipo {Giornaliero,Settimanale,Mensile,Annuale};

class ricorrenza : virtual public nota
{
public:

    ricorrenza(QString titolo, QString corpo,QDate date,QTime time,Tipo type);
    ricorrenza(QDomElement ricorrenza);
    virtual ~ricorrenza();

    virtual QDomElement XmlSerialize(QDomDocument doc) const;
    virtual QString ToString() const;

    //Get e Set
    Tipo getType() const;
    void setType(const Tipo &type);

    QDate getDate() const;
    void setDate(const QDate &date);

    QTime getTime() const;
    void setTime(const QTime &time);

    QString TipoToQString() const;
    Tipo QStringToTipo(QString stringa) const;

private:
    QDate _date;
    QTime _time;
    Tipo _type;
};

#endif // RICORRENZA_H
