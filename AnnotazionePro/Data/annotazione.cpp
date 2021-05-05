#include "annotazione.h"

Annotazione::Annotazione(QString titolo, QString descrizione): _titolo(titolo), _descrizione(descrizione)
{

}

QString Annotazione::getTitolo() const
{
    return _titolo;
}

void Annotazione::setTitolo(const QString &value)
{
    _titolo = value;
}

QString Annotazione::getDescrizione() const
{
    return _descrizione;
}

void Annotazione::setDescrizione(const QString &value)
{
    _descrizione = value;
}
