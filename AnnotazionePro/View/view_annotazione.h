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
#include <QTextEdit>
#include <QtDebug>
#include <QTime>


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
    QHBoxLayout *_mainLayout;
    QVBoxLayout *_opzioni, *_griglia;
    QLineEdit *_LineTitolo;
    QTextEdit *_LineCorpo;
    QComboBox *_tipologia;
    QCalendarWidget *_calendario;
    QDateTimeEdit *_ora;
    QHBoxLayout *_bottomBar;
    // Metodi
    void viewOpzioni();
    void viewGriglia();
    void VisualizzaNota();
    void VisualizzaPromemoria();
    void VisualizzaRicorrenza();
    void VisualizzaElenco();
    void VisualizzaSpesa();


private slots:

    void tipologiaIndexChanged(int);
    void onTextChanged();
};

#endif // VIEW_ANNOTAZIONE_H
