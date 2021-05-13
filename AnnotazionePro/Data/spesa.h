#ifndef SPESA_H
#define SPESA_H

#include "elenco.h"

struct type_spesa {
    QString value;
    double costo;
    bool isDone=0;
};

class spesa : virtual public elenco
{
public:
    spesa(QString titolo, QString descrizione);
    spesa(QString titolo, QString descrizione,const lista<type_spesa> &spesa);
    ~spesa();

    double CostoComplessivo() const;

    double CostoRimanente() const;

    double CostoAttuale() const;

    void addElemento(const QString &elemento, const double &prezzo);

    void addElemento(const type_spesa &value);

private:
    lista<type_spesa> _spesa;
};

#endif // SPESA_H
