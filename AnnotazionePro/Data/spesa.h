#ifndef SPESA_H
#define SPESA_H

#include "elenco.h"
#include "Util/type_spesa.h"
#include <QDomDocument>
#include <QDomElement>

class spesa : virtual public elenco
{
public:
    // costruttori
    spesa();
    spesa(QString titolo, QString descrizione);
    spesa(QString titolo, QString descrizione,const lista<type_spesa*> &spesa);
    spesa(QDomElement spesa);
    spesa(const spesa& spesa);

    // distruttore
    ~spesa();

    // metodi polimorfici
    virtual QDomElement XmlSerialize(QDomDocument doc) const;
    virtual QString ToString() const;

    // overloading operatori
    bool operator==(const spesa& s) const;
    bool operator!=(const spesa& s) const;
    spesa& operator=(const spesa& s);

    // Metodo Extra
    double CostoComplessivo() const;

    // Get & Set
    lista<type_spesa *> getSpesa() const;
    void setSpesa(const lista<type_spesa*> _newSpesa);

private:
    lista<type_spesa*> _spesa;
};

#endif // SPESA_H
