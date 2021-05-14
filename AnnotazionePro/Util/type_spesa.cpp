#include "type_spesa.h"

type_spesa::type_spesa() : type_elenco(), _cost()
{

}

type_spesa::type_spesa(const QString value,const double costo,const bool isDone) : type_elenco(value,isDone), _cost(costo)
{

}

type_spesa::~type_spesa()
{

}

double type_spesa::getCost() const
{
    return _cost;
}

void type_spesa::setCost(double cost)
{
    _cost = cost;
}
