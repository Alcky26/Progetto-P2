#include "metodo_tipo.h"


Tipo metodo_tipo::IntToTipo(const int _index)
{
    switch(_index) {
    case(0) : return Giornaliero; break;
    case(1) : return Settimanale; break;
    case(2) : return Mensile; break;
    case(3) : return Annuale; break;
    default: return Giornaliero; break;
    }

}
