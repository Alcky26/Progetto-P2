#include "nota.h"

Nota::Nota(QString titolo, QString corpo): Annotazione(titolo), _corpo(corpo)
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
