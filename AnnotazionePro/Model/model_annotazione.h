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
    // Costruttore & Distruttore
    model_annotazione();
    ~model_annotazione();

    // Metodi I\O da/su file
    void readFromFile(const QDomDocument& doc);
    QDomDocument saveFile() const;

    // Metodo Add
    void aggiungiAnnotazione(annotazione  *annotazione);
    // Metodi Get
    lista<annotazione*> getAnnotazioni() const;
    annotazione *getAnnotazione(const unsigned int i) const;
    //annotazione* getAnnotazioni(QString Titolo) const;

    // Clean
    void reset();

    /// Rimozione e Modifica
    void rimouviElemento(const annotazione *annot);
    bool modificaElemento(int _index,annotazione *annot);

    bool muoviElementoDx(const lista<annotazione*>::constiterator ci);
    bool muoviElementoSx(const lista<annotazione*>::constiterator ci);

    // Salvataggio
    bool deviSalvare() const;
    void salvato();
    // Metodo Extra
    static QStringList categorie();

private:
    bool _needToSave=false;
    lista<annotazione*> _annotazioni;

};

#endif // MODEL_ANNOTAZIONE_H
