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

QString nota::ToString() const
{
    QString testo;
    testo+=annotazione::ToString();
    return testo+"Corpo: "+getCorpo()+"; ";
}

QString nota::getCorpo() const
{
    return _corpo;
}

void nota::setCorpo(const QString &value)
{
    _corpo = value;
}

