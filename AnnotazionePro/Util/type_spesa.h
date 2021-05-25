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
    type_spesa( QString value,bool isDone ,double costo);
    ~type_spesa();
    //Get and Set
    double getCost() const;
    void setCost(double cost);

private:
    double _cost;
};

#endif // TYPE_SPESA_H
