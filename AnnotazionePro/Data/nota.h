#ifndef NOTA_H
#define NOTA_H

#include <QString>
#include "annotazione.h"
class Nota: virtual public Annotazione
{
public:
    Nota(QString titolo, QString descrizione, QString Corpo);
    ~Nota();
    //Get e Set
    QString getCorpo() const;
    void setCorpo(const QString &value);
    //Override Operatori di Confronto
    bool operator==(const Nota &n) const;
    bool operator!=(const Nota &n) const;

private:
    QString _corpo;
};

#endif // NOTA_H
