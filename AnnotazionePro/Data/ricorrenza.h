#ifndef RICORRENZA_H
#define RICORRENZA_H

#include "nota.h"
#include <QDate>
#include <QTime>

enum Tipo {Giornaliero,Settimanale,Mensile,Annuale, Personalizzato };

class ricorrenza : virtual public Nota
{
public:
    ricorrenza(QString titolo, QString descrizione, QString corpo,QDate date,QTime time,Tipo type);
    ~ricorrenza();
    //Get e Set
    Tipo getType() const;
    void setType(const Tipo &type);

    QDate getDate() const;
    void setDate(const QDate &date);

    QTime getTime() const;
    void setTime(const QTime &time);

    //Override Operatori di Confronto
    bool operator==(const ricorrenza &r) const;
    bool operator!=(const ricorrenza &r) const;
    //Override Operatore di Somma
    void operator+(const QString &value);


private:
    QDate _date;
    QTime _time;
    Tipo _type;
};

#endif // RICORRENZA_H
