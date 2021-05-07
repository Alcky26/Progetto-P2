#include "nota.h"

Nota::Nota(QString titolo, QString descrizione, QString corpo): Annotazione(titolo,descrizione), _corpo(corpo)
{

}

QString Nota::getCorpo() const
{
    return _corpo;
}

void Nota::setCorpo(const QString &value)
{
    _corpo = value;
}

bool Nota::operator==(const Nota &n) const
{
    return getTitolo()== n.getTitolo() &&
            getDescrizione()== n.getDescrizione() &&
            _corpo == n._corpo;
}

bool Nota::operator!=(const Nota &n) const
{
    return !operator==(n);
}

void Nota::operator+(const QString &value)
{
    _corpo += value;
}
