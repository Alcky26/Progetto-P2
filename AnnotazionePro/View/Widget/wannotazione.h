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
#include <QGroupBox>

class wAnnotazione : public QWidget
{
     Q_OBJECT
public:
    wAnnotazione(ModelAnnotazione *model, QWidget *parent = 0);

    void update();

private:
    //Modello
    ModelAnnotazione *_model;

    //GUI

    QHBoxLayout *mainLayout;

    QVBoxLayout *opzioni, *griglia, *viewLayoutAggiungi;

    QGridLayout *viewLayoutGriglia;

    QVBoxLayout *layoutAnnotazione;


    //void QPushButton::setMenu(QMenu *menu)

    //Input
    QLineEdit *_LineTitolo, *_LineCorpo, *_LineValori;
    QComboBox *_tipologia;

    //Custom Input



    //Azioni
    QPushButton *_scelta, *_aggiungi;


    //Extra
    QGroupBox *spacingOpzioni, *spacingGriglia;

    // Nuova Annotazione (?)
    void viewAggiungi();
    //void Modifica();

    void VisualizzaNota();
    void VisualizzaPromemoria();
    void VisualizzaRicorrenza();
    void VisualizzaElenco();
    void VisualizzaSpesa();

    bool InputValido();

    void Reset();


private slots:

    void tipologiaIndexChanged(int);
    //void btnAggiungiClicked();
   /*
        void btnModificaClicked();
        void btnRimuoviClicked();
        void cellaClicked(int, int);
        void checkboxChanged(int);*/
};

#endif // WANNOTAZIONE_H
