#ifndef RICORRENZA_H
#define RICORRENZA_H

#include "nota.h"
#include <QDate>
#include <QTime>
#include <QDomDocument>
#include <QDomElement>

enum Tipo {Giornaliero,Settimanale,Mensile,Annuale};

class ricorrenza : virtual public nota
{
public:
    ricorrenza(QString titolo, QString corpo,QDate date,QTime time,Tipo type);
    ricorrenza(QDomElement ricorrenza);
    virtual ~ricorrenza();

    virtual QDomElement XmlSerialize(QDomDocument doc) const;
    static QDate strToItaDate(const QString& date);
    static QString dateToItaStr(const QDate& date);
    //Get e Set
    Tipo getType() const;
    void setType(const Tipo &type);

    QDate getDate() const;
    void setDate(const QDate &date);

    QTime getTime() const;
    void setTime(const QTime &time);

    static QStringList getTipi();

    //Override Operatori di Confronto
    bool operator==(const ricorrenza &r) const;
    bool operator!=(const ricorrenza &r) const;

    //Metodi
    QString typeToQString() const;
    Tipo QStringToTipo(QString stringa) const;
    void Aggiorna();
    void Posticipa();

private:
    QDate _date;
    QTime _time;
    Tipo _type;
};

#endif // RICORRENZA_H
