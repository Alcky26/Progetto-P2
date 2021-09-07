#ifndef PROMEMORIA_H
#define PROMEMORIA_H

#include <QDate>
#include <QTime>
#include "nota.h"
#include <QDomDocument>
#include <QDomElement>
#include "Util/metodi_extra.h"


class promemoria : virtual public nota
{
public:
    // costruttori
    promemoria(QString titolo, QString corpo,QDate date,QTime time);
    promemoria(QDomElement promemoria);

    // distruttore
    virtual ~promemoria();

    // metodi polimorfi
    virtual QDomElement XmlSerialize(QDomDocument doc) const;
    virtual QString ToString() const;

    // overloadin operatori
    bool operator==(const promemoria& P) const;
    bool operator!=(const promemoria& P) const;
    promemoria &operator=(const promemoria& P);

    //Get & Set
    QDate getDate() const;
    void setDate(const QDate &date);

    QTime getTime() const;
    void setTime(const QTime &time);

private:
    QDate _date;
    QTime _time;
};

#endif // PROMEMORIA_H
