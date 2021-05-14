#ifndef TYPE_SPESA_H
#define TYPE_SPESA_H

#include <QString>
#include "Util/type_elenco.h"
/*
 * struct type_spesa : public elenchi{
     double costo;
  };*/
class type_spesa : virtual public type_elenco
{
public:
    //Costruttori e Distruttore
    type_spesa();
    type_spesa(const QString value,const double costo,const bool isDone=0);
    ~type_spesa();
    //Get and Set
    double getCost() const;
    void setCost(double cost);

private:
    double _cost;
};

#endif // TYPE_SPESA_H
