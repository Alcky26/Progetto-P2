#ifndef TYPE_ELENCO_H
#define TYPE_ELENCO_H

#include <QString>

class type_elenco
{
public:
    //Costruttore e Distruttore
    type_elenco();
    type_elenco(QString* value);
    type_elenco(QString value, bool isDone=0);

    virtual ~type_elenco();

    //Get & Set
    QString getValue() const;
    void setValue(const QString &value);

    bool getIsDone() const;
    void setIsDone(const bool value);

private:
    QString _value;
    bool _isDone;
};

#endif // TYPE_ELENCO_H
