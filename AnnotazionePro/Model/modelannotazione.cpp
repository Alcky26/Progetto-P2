#include "modelannotazione.h"

ModelAnnotazione::ModelAnnotazione() : _needToSave(false),_annotazioni()
{

}

void ModelAnnotazione::aggiungiAnnotazione(annotazione *annotazione)
{
    _annotazioni.insertBack(annotazione);
    _needToSave=true;
}

lista<annotazione *> ModelAnnotazione::getAnnotazioni() const
{
    return _annotazioni;
}

void ModelAnnotazione::reset()
{
    _annotazioni.clear();
}

void ModelAnnotazione::rimouviElemento(annotazione *annot)
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

bool ModelAnnotazione::deviSalvare() const
{
    return _needToSave;
}

void ModelAnnotazione::salvato()
{
    _needToSave = false;
}

QStringList ModelAnnotazione::categorie()
{
    QStringList tipologieItems;
    tipologieItems.push_back("Nota");
    tipologieItems.push_back("Promemoria");
    tipologieItems.push_back("Ricorrenza");
    tipologieItems.push_back("Elenco");
    tipologieItems.push_back("Spesa");
    return tipologieItems;
}

