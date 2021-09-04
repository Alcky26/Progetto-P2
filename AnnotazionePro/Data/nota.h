#ifndef nota_H
#define nota_H

#include <QString>
#include "annotazione.h"
#include <QDomDocument>
#include <QDomElement>
class nota: virtual public annotazione
{
public:
    // Costruttori
    nota(QString titolo, QString Corpo);
    nota(QDomElement nota);
    // Distruttore
    virtual ~nota();

    virtual QDomElement XmlSerialize(QDomDocument doc) const;

    virtual QString ToString() const;

    //Get & Set
    QString getCorpo() const;
    void setCorpo(const QString &value);

private:
    QString _corpo;
};

#endif // nota_H
