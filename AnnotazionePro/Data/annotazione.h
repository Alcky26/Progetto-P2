#ifndef ANNOTAZIONE_H
#define ANNOTAZIONE_H

#include <QString>
class annotazione
{
public:
    annotazione(QString titolo);
    annotazione();
    virtual ~annotazione()=0;


    QString getTitolo() const;
    void setTitolo(const QString &value);

private:
    QString _titolo;

};

#endif // ANNOTAZIONE_H
