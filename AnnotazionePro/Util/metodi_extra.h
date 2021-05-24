#ifndef METODI_EXTRA_H
#define METODI_EXTRA_H

#include "type_elenco.h"
#include "type_spesa.h"
#include "lista.h"
#include <QString>
#include <QStringList>


class metodi_extra
{
public:

    //Metodi da mettere su file a parte
    static lista<type_elenco *> TextToTypeElenco(QString &Testo);
    static lista<type_spesa *> TextToTypeSpesa(QString Testo);
};

#endif // METODI_EXTRA_H
