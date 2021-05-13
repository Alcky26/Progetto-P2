#ifndef SPESA_H
#define SPESA_H

#include "elenco.h"

struct spese {
    QString value;
    double costo;
    bool isDone=0;
};

class spesa : virtual public elenco
{
public:
    spesa(QString titolo, QString descrizione);
    spesa(QString titolo, QString descrizione,const lista<spese> &spesa);
    ~spesa();

    double CostoComplessivo() const;

    double CostoRimanente() const;

    double CostoAttuale() const;

    void addElemento(const QString &elemento, const double &prezzo);

    void addElemento(const spese &value);

private:
    lista<spese> _spesa;
};

#endif // SPESA_H
