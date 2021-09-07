#ifndef TYPE_ELENCO_H
#define TYPE_ELENCO_H

#include <QString>

class type_elenco
{
public:
    // costruttori
    type_elenco();
    type_elenco(QString* value);
    type_elenco(QString value, bool isDone=0);

    // distruttore
    virtual ~type_elenco();

    //Get & Set
    QString getValue() const;
    void setValue(const QString &value);

    bool getIsDone() const;
    void setIsDone(const bool value);

    // overloading operatore

    bool operator==(const type_elenco& t) const;
    bool operator!=(const type_elenco& t) const;
    type_elenco& operator=(const type_elenco& t)
    {
        if(this!=&t)
        {
            _value=t.getValue();
            _isDone=t.getIsDone();
        }
        return *this;
    }

private:
    QString _value;
    bool _isDone;
};

#endif // TYPE_ELENCO_H
