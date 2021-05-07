#ifndef PROMEMORIA_H
#define PROMEMORIA_H

#include <QDate>
#include <QTime>
#include "nota.h"

class promemoria : virtual public Nota
{
public:
    promemoria(QString titolo, QString descrizione, QString corpo,QDate date,QTime time);
    ~promemoria();
    //Get e Set
    QDate getDate() const;
    void setDate(const QDate &date);

    QTime getTime() const;
    void setTime(const QTime &time);
    //Override Operatori di Confronto
    bool operator==(const promemoria &p) const;
    bool operator!=(const promemoria &p) const;
    //Override Operatore di Somma
    void operator+(const QString &value);

private:
    QDate _date;
    QTime _time;
};

#endif // PROMEMORIA_H
