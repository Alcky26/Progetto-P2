#include "nota.h"

nota::nota(QString titolo, QString corpo): annotazione(titolo), _corpo(corpo)
{

}

nota::nota(QDomElement nota):
    annotazione(nota.childNodes().at(0).toElement()),
    _corpo(nota.attribute("Corpo"))
{

}

nota::~nota()
{

}

QDomElement nota::XmlSerialize(QDomDocument doc) const
{
    QDomElement nota = doc.createElement("Nota");
    nota.appendChild(annotazione::XmlSerialize(doc));
    nota.setAttribute("Corpo", _corpo);
    return nota;
}

QString nota::getCorpo() const
{
    return _corpo;
}

void nota::setCorpo(const QString &value)
{
    _corpo = value;
}

bool nota::operator==(const nota &n) const
{
    return getTitolo()== n.getTitolo() &&
            _corpo == n._corpo;
}

bool nota::operator!=(const nota &n) const
{
    return !operator==(n);
}

void nota::operator+(const QString &value)
{
    _corpo += value;
}
