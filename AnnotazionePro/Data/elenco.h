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

    virtual QDomElement XmlSerialize(QDomDocument doc) const;
    virtual QString ToString() const;

    QString getDescrizione() const;
    void setDescrizione(const QString  &descrizione);

    lista<type_elenco *> getElenco() const;
    void setElenco(const lista<type_elenco*> _newElenco);

    void addElemento(const QString* &elemento);
    void Remove(const type_elenco* &_this);

private:
    QString _descrizione;
    lista<type_elenco*> _elenco;
};

#endif // ELENCO_H
