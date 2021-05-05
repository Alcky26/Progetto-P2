#include "annotazione.h"

Annotazione::Annotazione(QString titolo, QString descrizione): Titolo(titolo),Descrizione(descrizione)
{

}

QString Annotazione::getTitolo() const
{
    return Titolo;
}

void Annotazione::setTitolo(const QString &value)
{
    Titolo = value;
}

QString Annotazione::getDescrizione() const
{
    return Descrizione;
}

void Annotazione::setDescrizione(const QString &value)
{
    Descrizione = value;
}
