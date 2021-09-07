#ifndef ANNOTAZIONE_H
#define ANNOTAZIONE_H

#include <QString>
#include <QDomDocument>
#include <QDomElement>
class annotazione
{
public:
    // costruttori
    annotazione(QString titolo);
    annotazione();
    annotazione(QDomElement ann);

    // distruttore
    virtual ~annotazione()=0;

    // metodi polimorfi
    virtual QDomElement XmlSerialize(QDomDocument doc) const;
    virtual QString ToString() const;

    // overloading operatori
    bool operator==(const annotazione& A) const;
    bool operator!=(const annotazione& A) const;
    annotazione &operator=(const annotazione& A);

    // Get & Set
    QString getTitolo() const;
    void setTitolo(const QString &value);

private:
    QString _titolo;

};

#endif // ANNOTAZIONE_H
