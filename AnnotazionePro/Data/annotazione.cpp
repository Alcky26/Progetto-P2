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

QString annotazione::ToString() const
{
    return "Titolo: "+getTitolo()+"; ";
}

bool annotazione::operator==(const annotazione& A) const {
    return A.getTitolo()==_titolo;
}

bool annotazione::operator!=(const annotazione &A) const {
    return !(this==&A);
}

annotazione &annotazione::operator=(const annotazione &A)
{
    if(this!=&A)
        _titolo= A.getTitolo();
    return *this;
}

QString annotazione::getTitolo() const
{
    return _titolo;
}

void annotazione::setTitolo(const QString &value)
{
    _titolo = value;
}

