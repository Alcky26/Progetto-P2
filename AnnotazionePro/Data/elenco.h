#ifndef ELENCO_H
#define ELENCO_H

#include <QString>
#include "Util/lista.h"
#include "annotazione.h"
#include "Util/type_elenco.h"


class elenco: virtual public annotazione
{
public:
    elenco();
    elenco(QString titolo, QString descrizione);
    elenco(QString titolo, QString descrizione,lista<QString*> &elenco);
    elenco(QString titolo, QString descrizione,lista<type_elenco*> elenco);
    virtual ~elenco();

    ///Override Operatore di Somma
    ///void operator+(const QString &value);

    QString getListAsText();

    QString getDescrizione() const;
    void setDescrizione(QString const &descrizione);

    void addElemento(const QString* &elemento);

private:
    QString _descrizione;
    lista<type_elenco*> _elenco;
};

#endif // ELENCO_H
