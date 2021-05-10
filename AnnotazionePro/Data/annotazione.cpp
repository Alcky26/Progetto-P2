#include "annotazione.h"

Annotazione::Annotazione(QString titolo): _titolo(titolo)
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

