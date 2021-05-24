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
    QStringList _NewSupportList;

    for(QStringList::ConstIterator cit =_SupportList.begin(); cit != _SupportList.end(); cit++)
    {
        _NewSupportList.append((cit)->split(','));
    }

    lista<type_spesa*> _endResult;
    try {
        for(QStringList::ConstIterator cit=_NewSupportList.begin(); cit != _NewSupportList.end(); cit++)
        {
           if(! (cit==_NewSupportList.end() ) )
           {
               _endResult.insertFront(new type_spesa(* (cit),(*(cit+1)).toDouble(),false));
           }
           else
                _endResult.insertFront(new type_spesa(* (cit),0,false));
        }

    }  catch (_exception e) {
        //PORCO IL CAZZO

    }

    return _endResult;
}
