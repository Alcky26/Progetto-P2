#include "type_elenco.h"

type_elenco::type_elenco() : _value(), _isDone(0)
{

}

type_elenco::type_elenco(QString* value) : _value(*value), _isDone(0)
{

}

type_elenco::type_elenco(QString value, bool isDone) : _value(value), _isDone(isDone)
{

}

type_elenco::~type_elenco()
{

}

QString type_elenco::getValue() const
{
    return _value;
}

void type_elenco::setValue(const QString &value)
{
    _value = value;
}

bool type_elenco::operator==(const type_elenco& t) const {
    return _value==t.getValue() && _isDone==t.getIsDone();
}

bool type_elenco::getIsDone() const
{
    return _isDone;
}

void type_elenco::setIsDone(const bool value)
{
    _isDone = value;
}


