#ifndef ANNOTAZIONE_H
#define ANNOTAZIONE_H

#include <QString>
#include <QDomDocument>
#include <QDomElement>
class annotazione
{
public:
    annotazione(QString titolo);
    annotazione();
    annotazione(QDomElement ann);
    virtual ~annotazione()=0;

    virtual QDomElement XmlSerialize(QDomDocument doc) const;

    virtual QString ToString() const;

    QString getTitolo() const;
    void setTitolo(const QString &value);

private:
    QString _titolo;

};

#endif // ANNOTAZIONE_H
