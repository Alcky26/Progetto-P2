#ifndef ANNOTAZIONE_H
#define ANNOTAZIONE_H

#include <QString>
class Annotazione
{
public:
    Annotazione(QString titolo, QString descrizione);
    virtual ~Annotazione()=0;


    QString getTitolo() const;
    void setTitolo(const QString &value);

    QString getDescrizione() const;
    void setDescrizione(const QString &value);

private:
    QString _titolo;
    QString _descrizione;

};

#endif // ANNOTAZIONE_H
