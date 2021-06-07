#ifndef METODI_EXTRA_H
#define METODI_EXTRA_H

#include "type_elenco.h"
#include "type_spesa.h"
#include "lista.h"
#include <QString>
#include <QStringList>
#include "Data/ricorrenza.h"

class metodi_extra
{
public:

    //Metodi da mettere su file a parte
    static Tipo MetodoSupporto(int _index);
    static QString ElencoAsText(lista<type_elenco*> _elenco);
    static QString SpesaAsText(lista<type_spesa*> _spesa);
};

#endif // METODI_EXTRA_H
