#ifndef WANNOTAZIONE_H
#define WANNOTAZIONE_H

#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "Util/lista.h"
#include <QPushButton>


class wAnnotazione :public QWidget
{
     Q_OBJECT
public:
    wAnnotazione();

    void update();
private:
    //Modello


    //GUI
    QGridLayout *mainLayout;
    QVBoxLayout *opzioni;

    //QLabel
    //QLineEdit
    //void QPushButton::setMenu(QMenu *menu)

    //Input
    QLineEdit *titolo, *descrizione, *values;


    //Custom Input



    //Azioni
    QPushButton *scelta, *aggiungi;


    //Extra
    QLabel *_titolo, *_descrizione,*_values;


    void Aggiungi();
    void Change();

    bool InputValido();

    void Reset();


private slots:
    void btnAggiungiClicked();
   /* void tipologiaIndexChanged(int);

        void btnModificaClicked();
        void btnRimuoviClicked();
        void cellaClicked(int, int);
        void checkboxChanged(int);*/
};

#endif // WANNOTAZIONE_H
