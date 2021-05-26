#include "model_annotazione.h"

model_annotazione::model_annotazione() : _needToSave(false),_annotazioni()
{

}

void model_annotazione::aggiungiAnnotazione(annotazione *annotazione)
{
    _annotazioni.insertBack(annotazione);
    _needToSave=true;
}

lista<annotazione *> model_annotazione::getAnnotazioni() const
{
    return _annotazioni;
}

annotazione *model_annotazione::getAnnotazione(unsigned int i) const
{
    if( _annotazioni.getSize()<i)
    {
        return nullptr;
    }
    else
    {
        unsigned int _counter = 0;
        for(lista<annotazione*>::constiterator ci=_annotazioni.begin();ci!=_annotazioni.end();ci++)
        {
            if(_counter == i)
                return *ci;
            _counter++;
        }
    }
    return nullptr;
}

void model_annotazione::reset()
{
    _annotazioni.clear();
}

void model_annotazione::rimouviElemento(annotazione *annot)
{

    lista<annotazione *>::constiterator ci = _annotazioni.begin();
    bool _eliminato = false;

    while( ci != _annotazioni.end() || _eliminato == false)
    {
        if(*ci == annot)
        {
            _annotazioni.erase(ci);
            _eliminato=true;
        }
        ci++;
    }

}

bool model_annotazione::deviSalvare() const
{
    return _needToSave;
}

void model_annotazione::salvato()
{
    _needToSave = false;
}

QStringList model_annotazione::categorie()
{
    QStringList tipologieItems;
    tipologieItems.push_back("Nota");
    tipologieItems.push_back("Promemoria");
    tipologieItems.push_back("Ricorrenza");
    tipologieItems.push_back("Elenco");
    tipologieItems.push_back("Spesa");
    return tipologieItems;
}

