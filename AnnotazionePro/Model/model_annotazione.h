#ifndef MODEL_ANNOTAZIONE_H
#define MODEL_ANNOTAZIONE_H

#include "Util/lista.h"
#include "Data/annotazione.h"
#include <QStringList>

class model_annotazione
{
public:
    model_annotazione();

    //void ReadFile();
    //QDomDocument SaveFile();

    void aggiungiAnnotazione(annotazione *annotazione);
    // getter
    lista<annotazione*> getAnnotazioni() const;
    annotazione *getAnnotazione(unsigned int i) const;
    //annotazione* getAnnotazioni(QString Titolo) const;

    void reset();
////////////// METODO MODIFICADI UN ELEMENTO ???????!??!?!??!?!?!?!?!?
    void rimouviElemento(annotazione *annot);

    bool deviSalvare() const;
    void salvato();
    static QStringList categorie();

private:
    bool _needToSave=false;
    lista<annotazione*> _annotazioni;

};

#endif // MODEL_ANNOTAZIONE_H
