#ifndef METODI_EXTRA_H
#define METODI_EXTRA_H

#include "type_elenco.h"
#include "type_spesa.h"
#include "lista.h"
#include <QString>
#include <QStringList>
#include <QDate>


class metodi_extra
{
public:

    //Metodi da mettere su file a parte
    static QString ElencoAsText(const lista<type_elenco*> _elenco);
    static QString SpesaAsText(const lista<type_spesa*> _spesa);
    static QStringList getTipi();

    static QString dateToItaStr(const QDate& date);
    static QDate strToItaDate(const QString& date);
};

#endif // METODI_EXTRA_H
