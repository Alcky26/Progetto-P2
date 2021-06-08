#ifndef MODEL_ANNOTAZIONE_H
#define MODEL_ANNOTAZIONE_H

#include "Util/lista.h"
#include "Data/annotazione.h"
#include "Data/nota.h"
#include "Data/ricorrenza.h"
#include "Data/promemoria.h"
#include "Data/elenco.h"
#include "Data/spesa.h"
#include <QStringList>
#include <QDomDocument>
#include <QDomElement>

class model_annotazione
{
public:
    model_annotazione();
    ~model_annotazione();

    void readFromFile(const QDomDocument& doc);
    QDomDocument saveFile() const;

    void aggiungiAnnotazione(annotazione  *annotazione);
    // getter
    lista<annotazione*> getAnnotazioni() const;
    annotazione *getAnnotazione(const unsigned int i) const;
    //annotazione* getAnnotazioni(QString Titolo) const;

    void reset();

    /// METODO MODIFICA DI UN ELEMENTO
    void rimouviElemento(const annotazione *annot);
    void modificaElemento(int _index,annotazione *annot);

    bool muoviElementoDx(const lista<annotazione*>::constiterator ci);
    bool muoviElementoSx(const lista<annotazione*>::constiterator ci);

    bool deviSalvare() const;
    void salvato();
    static QStringList categorie();

private:
    bool _needToSave=false;
    lista<annotazione*> _annotazioni;

};

#endif // MODEL_ANNOTAZIONE_H
