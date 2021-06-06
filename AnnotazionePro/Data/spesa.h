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

    double CostoComplessivo() const;

    double CostoRimanente() const;

    double CostoAttuale() const;

    QString getListSpesaAsText();

    void addElement(const QString &elemento, const double &prezzo);

    void addElement(type_spesa* const &value);

    void Remove(const QString &elemento, const double &prezzo);

    lista<type_spesa *> getSpesa() const;
     void setSpesa( lista<type_spesa*> _newSpesa);

private:
    lista<type_spesa*> _spesa;
};

#endif // SPESA_H
