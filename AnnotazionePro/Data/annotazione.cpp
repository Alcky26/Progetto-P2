#include "annotazione.h"

annotazione::annotazione(QString titolo): _titolo(titolo)
{

}

annotazione::annotazione():_titolo("")
{

}

QString annotazione::getTitolo() const
{
    return _titolo;
}

void annotazione::setTitolo(const QString &value)
{
    _titolo = value;
}

