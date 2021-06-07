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
    static ricorrenza::Tipo IntToTipo(int _index);
    static ricorrenza::Tipo QStringToTipo(QString stringa);
    static QString TipoToQString(ricorrenza::Tipo _type);
    static QString ElencoAsText(lista<type_elenco*> _elenco);
    static QString SpesaAsText(lista<type_spesa*> _spesa);
    static QDate strToItaDate(const QString& date) ;
    static QString dateToItaStr(const QDate& date);
    static QStringList getTipi();
};

#endif // METODI_EXTRA_H
