#ifndef ELENCO_H
#define ELENCO_H

#include <QString>
#include "Util/lista.h"
#include "annotazione.h"

struct elenchi {
    QString value;
    bool isDone=0;
};

class elenco: virtual public annotazione
{
public:
    elenco(QString titolo, QString descrizione);
    elenco(QString titolo, QString descrizione,const lista<QString> &elenco);
    virtual ~elenco();

    ///Override Operatore di Somma
    ///void operator+(const QString &value);

    QString descrizione() const;
    void setDescrizione(const QString &descrizione);

    void addElemento(const QString &elemento);

private:
    QString _descrizione;
    lista<elenchi> _elenco;
};

#endif // ELENCO_H
