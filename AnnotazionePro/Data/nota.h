#ifndef NOTA_H
#define NOTA_H

#include <QString>
#include "annotazione.h"
class Nota: virtual public Annotazione
{
public:
    Nota(QString titolo, QString descrizione, QString Corpo);
    ~Nota();

    QString getCorpo() const;
    void setCorpo(const QString &value);

    bool operator==(const Nota &n) const;

    bool operator!=(const Nota &n) const;

private:
    QString _corpo;
};

#endif // NOTA_H
