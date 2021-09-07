#ifndef nota_H
#define nota_H

#include <QString>
#include "annotazione.h"
#include <QDomDocument>
#include <QDomElement>
class nota: virtual public annotazione
{
public:
    // costruttori
    nota(QString titolo, QString Corpo);
    nota(QDomElement nota);

    // distruttore
    virtual ~nota();

    // metodi polimorfi
    virtual QDomElement XmlSerialize(QDomDocument doc) const;
    virtual QString ToString() const;

    // overloading operatori
    bool operator==(const nota& N) const;
    bool operator!=(const nota& N) const;
    nota& operator=(const nota& N);

    // Get & Set
    QString getCorpo() const;
    void setCorpo(const QString &value);

private:
    QString _corpo;
};

#endif // nota_H
