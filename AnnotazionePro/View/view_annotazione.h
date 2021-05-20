#ifndef VIEW_ANNOTAZIONE_H
#define VIEW_ANNOTAZIONE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QCalendarWidget>
#include <QDateTimeEdit>
#include "Model/model_annotazione.h"


class view_annotazione : public QWidget
{
    Q_OBJECT
public:
    // Costruttore
    view_annotazione(model_annotazione *model, QWidget *parent = 0);

private:
    // Modello
    model_annotazione *_model;

    // GUI
    QHBoxLayout *mainLayout;
    QVBoxLayout *opzioni, *griglia;
    QLineEdit *_LineTitolo,*_LineCorpo;
    QComboBox *_tipologia;
    QCalendarWidget *_calendario;
    QDateTimeEdit *_ora;
    // Metodi
    void viewOpzioni();
    void VisualizzaNota();
    void VisualizzaPromemoria();
    void VisualizzaRicorrenza();
    void VisualizzaElenco();
    void VisualizzaSpesa();

private slots:

    void tipologiaIndexChanged(int);
};

#endif // VIEW_ANNOTAZIONE_H
