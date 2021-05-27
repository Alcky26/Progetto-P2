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
    while( ci != _annotazioni.end() && _eliminato == false)
    {
        if(*ci == annot)
        {
            _annotazioni.erase(ci);
            _eliminato=true;
        }
        ci++;
    }
}

void model_annotazione::modificaElemento(int _index,annotazione *annot)
{
    int i=0;
    for(lista<annotazione*>::constiterator ci=_annotazioni.begin();ci!=_annotazioni.end();ci++)
    {

        if(i==_index)
        {
            (*ci)->setTitolo(annot->getTitolo());
            if(dynamic_cast<promemoria*>(*ci))
            {
               dynamic_cast<promemoria*>(*ci)->setDate(dynamic_cast<promemoria*>(annot)->getDate());
               dynamic_cast<promemoria*>(*ci)->setTime(dynamic_cast<promemoria*>(annot)->getTime());
            }
            else if(dynamic_cast<ricorrenza*>(*ci))
            {
                dynamic_cast<ricorrenza*>(*ci)->setDate(dynamic_cast<ricorrenza*>(annot)->getDate());
                dynamic_cast<ricorrenza*>(*ci)->setTime(dynamic_cast<ricorrenza*>(annot)->getTime());
            }
            else if(dynamic_cast<elenco*>(*ci))
            {
                dynamic_cast<elenco*>(*ci)->setDescrizione(dynamic_cast<elenco*>(annot)->getDescrizione());
                dynamic_cast<elenco*>(*ci)->setElenco(dynamic_cast<elenco*>(annot)->getElenco());
            }
            else if(dynamic_cast<spesa*>(*ci))
            {
                dynamic_cast<spesa*>(*ci)->setDescrizione(dynamic_cast<spesa*>(annot)->getDescrizione());
                dynamic_cast<spesa*>(*ci)->setElenco(dynamic_cast<spesa*>(annot)->getElenco());
            }

            if(dynamic_cast<nota*>(*ci))
            {
                dynamic_cast<nota*>(*ci)->setCorpo(dynamic_cast<nota*>(annot)->getCorpo());
            }
        }
        i++;
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

