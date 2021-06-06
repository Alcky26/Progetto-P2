#ifndef ELENCO_H
#define ELENCO_H

#include <QString>
#include "Util/lista.h"
#include "annotazione.h"
#include "Util/type_elenco.h"
#include <QDomDocument>
#include <QDomElement>

class elenco: virtual public annotazione
{
public:
    elenco();
    elenco(QString titolo, QString descrizione);
    elenco(QString titolo, QString descrizione,lista<QString*> &elenco);
    elenco(QString titolo, QString descrizione,lista<type_elenco*> elenco);
    elenco(const elenco& elen);
    elenco(QDomElement elenco);
    virtual ~elenco();

    ///Override Operatore di Somma
    ///void operator+(const QString &value);

    virtual QDomElement XmlSerialize(QDomDocument doc) const;

    QString getListAsText();

    QString getDescrizione() const;

    void setElenco( lista<type_elenco*> _newElenco);
    void setDescrizione(QString const &descrizione);

    void addElemento(const QString* &elemento);

    lista<type_elenco *> getElenco() const;

private:
    QString _descrizione;
    lista<type_elenco*> _elenco;
};

#endif // ELENCO_H
