#include "type_elenco.h"

type_elenco::type_elenco() : _value(), _isDone(0)
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

bool type_elenco::getIsDone() const
{
    return _isDone;
}

void type_elenco::setIsDone(bool value)
{
    _isDone = value;
}