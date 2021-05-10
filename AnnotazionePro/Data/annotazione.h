#ifndef ANNOTAZIONE_H
#define ANNOTAZIONE_H

#include <QString>
class Annotazione
{
public:
    Annotazione(QString titolo);
    virtual ~Annotazione()=0;


    QString getTitolo() const;
    void setTitolo(const QString &value);

private:
    QString _titolo;

};

#endif // ANNOTAZIONE_H
