#ifndef WANNOTAZIONE_H
#define WANNOTAZIONE_H

#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "Util/lista.h"
#include <QPushButton>
#include <QComboBox>
#include "Model/modelannotazione.h"

class wAnnotazione : public QWidget
{
     Q_OBJECT
public:
    wAnnotazione(ModelAnnotazione *model, QWidget *parent);

    void update();

private:
    //Modello
    ModelAnnotazione *_model;

    //GUI
    QVBoxLayout *mainLayout,*opzioni;
    QGridLayout *griglia;

    QGridLayout *viewLayoutAggiungi;

    //QLabel
    //QLineEdit
    //void QPushButton::setMenu(QMenu *menu)

    //Input
    QLineEdit *_LineTitolo, *_LineDescrizione, *_LineValori;
    QComboBox *_tipologia;

    //Custom Input



    //Azioni
    QPushButton *_scelta, *_aggiungi;


    //Extra


    // Nuova Annotazione (?)
    void viewAggiungi();
    //void Modifica();

    bool InputValido();

    void Reset();


private slots:
    //void btnAggiungiClicked();
   /* void tipologiaIndexChanged(int);

        void btnModificaClicked();
        void btnRimuoviClicked();
        void cellaClicked(int, int);
        void checkboxChanged(int);*/
};

#endif // WANNOTAZIONE_H
