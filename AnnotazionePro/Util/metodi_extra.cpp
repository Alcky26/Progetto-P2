#include "metodi_extra.h"



lista<type_elenco *> metodi_extra::TextToTypeElenco(QString &Testo)
{

    QStringList _SupportList = Testo.split(';');
    lista<type_elenco*> _endResult;

    for(QStringList::ConstIterator cit=_SupportList.begin(); cit != _SupportList.end(); cit++)
    {

        _endResult.insertFront(new type_elenco(* (cit),false));
    }

    return _endResult;
}

lista<type_spesa *> metodi_extra::TextToTypeSpesa(QString Testo)
{

    QStringList _SupportList = Testo.split(';');
    lista<type_spesa*> _endResult;

    for(QStringList::ConstIterator cit=_SupportList.begin(); cit != _SupportList.end(); cit=cit+2)
    {

        _endResult.insertFront(new type_spesa(* (cit),(*(cit+1)).toDouble(),false));
    }

    return _endResult;
}
