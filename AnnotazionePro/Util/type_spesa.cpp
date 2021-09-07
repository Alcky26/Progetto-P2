#include "type_spesa.h"

type_spesa::type_spesa() : type_elenco(), _cost()
{

}

type_spesa::type_spesa( QString value, bool isDone, double costo) : type_elenco(value,isDone), _cost(costo)
{

}

type_spesa::~type_spesa()
{

}

bool type_spesa::operator==(const type_spesa &ts) const {
    return ts.getCost()==_cost && type_elenco::operator==(ts);
}

bool type_spesa::operator!=(const type_spesa &ts) const
{
    return !(this==&ts);
}

type_spesa &type_spesa::operator=(const type_spesa &ts)
{
    if(this!=&ts)
    {
        _cost=ts.getCost();
        setIsDone((ts.getIsDone()));
        setValue(ts.getValue());
    }
    return *this;
}

double type_spesa::getCost() const
{
    return _cost;
}

void type_spesa::setCost(const double cost)
{
    _cost = cost;
}
