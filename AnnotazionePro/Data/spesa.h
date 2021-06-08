#ifndef SPESA_H
#define SPESA_H

#include "elenco.h"
#include <QDebug>
#include "Util/type_spesa.h"
#include <QDomDocument>
#include <QDomElement>

class spesa : virtual public elenco
{
public:
    spesa();
    spesa(QString titolo, QString descrizione);
    spesa(QString titolo, QString descrizione,const lista<type_spesa*> &spesa);
    spesa(QDomElement spesa);
    spesa(const spesa& spes);
    ~spesa();

    virtual QDomElement XmlSerialize(QDomDocument doc) const;
    virtual QString ToString() const;

    double CostoComplessivo() const;

    void addElement(const QString &elemento, const double &prezzo);

    void addElement(const type_spesa* &value);

    void Remove(const type_spesa* &_this);

    lista<type_spesa *> getSpesa() const;
    void setSpesa(const lista<type_spesa*> _newSpesa);

private:
    lista<type_spesa*> _spesa;
};

#endif // SPESA_H
