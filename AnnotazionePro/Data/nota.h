#ifndef nota_H
#define nota_H

#include <QString>
#include "annotazione.h"
class nota: virtual public annotazione
{
public:
    nota(QString titolo, QString Corpo);
    virtual ~nota();
    //Get e Set
    QString getCorpo() const;
    void setCorpo(const QString &value);
    //Override Operatori di Confronto
    bool operator==(const nota &n) const;
    bool operator!=(const nota &n) const;
    //Override Operatore di Somma
    void operator+(const QString &value);
private:
    QString _corpo;
};

#endif // nota_H
