#include "annotazione.h"

annotazione::annotazione(QString titolo): _titolo(titolo)
{

}

annotazione::annotazione():_titolo("")
{

}

annotazione::annotazione(QDomElement ann):_titolo(ann.attribute("Titolo"))
{

}

annotazione::~annotazione()
{

}

QDomElement annotazione::XmlSerialize(QDomDocument doc) const
{
    QDomElement ann = doc.createElement("Annotazione");
    ann.setAttribute("Titolo", _titolo);
    return ann;
}

QString annotazione::getTitolo() const
{
    return _titolo;
}

void annotazione::setTitolo(const QString &value)
{
    _titolo = value;
}

