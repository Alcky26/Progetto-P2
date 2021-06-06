#ifndef PROMEMORIA_H
#define PROMEMORIA_H

#include <QDate>
#include <QTime>
#include "nota.h"
#include <QDomDocument>
#include <QDomElement>

class promemoria : virtual public nota
{
public:
    promemoria(QString titolo, QString corpo,QDate date,QTime time);
    promemoria(QDomElement promemoria);
    virtual ~promemoria();

    virtual QDomElement XmlSerialize(QDomDocument doc) const;
    static QDate strToItaDate(const QString& date);
    static QString dateToItaStr(const QDate& date);

    //Get e Set
    QDate getDate() const;
    void setDate(const QDate &date);

    QTime getTime() const;
    void setTime(const QTime &time);
    //Override Operatori di Confronto
    bool operator==(const promemoria &p) const;
    bool operator!=(const promemoria &p) const;

private:
    QDate _date;
    QTime _time;
};

#endif // PROMEMORIA_H
