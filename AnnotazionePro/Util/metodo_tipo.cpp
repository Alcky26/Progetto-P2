#include "metodo_tipo.h"


Tipo metodo_tipo::IntToTipo(const int _index)
{
    Tipo _nuovoTipo=Giornaliero;

    if(_index==0)
        _nuovoTipo = Giornaliero;
    else if (_index == 1)
        _nuovoTipo = Settimanale;
    else if (_index == 2)
       _nuovoTipo = Mensile;
    else if (_index == 3)
       _nuovoTipo = Annuale;

    return _nuovoTipo;
}