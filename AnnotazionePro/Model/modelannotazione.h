#ifndef MODELANNOTAZIONE_H
#define MODELANNOTAZIONE_H

#include "Util/lista.h"
#include "Data/annotazione.h"
#include <QStringList>

class ModelAnnotazione
{
public:
    ModelAnnotazione();

    //void ReadFile();
    //QDomDocument SaveFile();

    void aggiungiAnnotazione(annotazione *annotazione);
    // getter
    lista<annotazione*> getAnnotazioni() const;
    //annotazione* getAnnotazioni(QString Titolo) const;

    void reset();

    void rimouviElemento(annotazione *annot);

    bool deviSalvare() const;
    void salvato();
    static QStringList categorie();

private:
    bool _needToSave=false;
    lista<annotazione*> _annotazioni;

};

#endif // MODELANNOTAZIONE_H
