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
#include "Data/annotazione.h"
#include "Data/nota.h"
#include "Data/ricorrenza.h"
#include "Data/promemoria.h"
#include "Data/elenco.h"
#include "Data/spesa.h"
#include "View/Widget/wannotazione.h"
#include <QGraphicsView>
#include <QScrollBar>
#include <QMessageBox>


class view_annotazione : public QWidget
{
    Q_OBJECT
public:
    // Costruttore
    view_annotazione(model_annotazione *model, QWidget *parent = 0);

private:
    // Modello
    model_annotazione *_model;
    lista<wAnnotazione*> _wA;

    // GUI
    QHBoxLayout *_mainLayout;
    // 2 Aree Principali
    QVBoxLayout *_opzioni;
    QVBoxLayout *_griglia;
    //Elementi per Inserimento
    QLineEdit *_LineTitolo;
    QTextEdit *_LineCorpo;
    QComboBox *_tipologia;   
    QCalendarWidget *_calendario;
    QDateTimeEdit *_ora;
    QComboBox *_tipo;
    QLabel *_ListHelp;
    QTextEdit *_LineList;
    QPushButton *_aggiunta;
    QPushButton *_aggiorna;

    // Metodi
    void viewOpzioni();
    void viewGriglia();

    void VisualizzaNota();
    void VisualizzaPromemoria();
    void VisualizzaRicorrenza();
    void VisualizzaElenco();
    void VisualizzaSpesa();

    void aggiornaGriglia(QGridLayout *supplay);
    void clearGriglia();
    void resizeAnn(wAnnotazione* Ann);

    Tipo MetodoSupporto(int _index) ;
    void AggiuntaAnnotazione();

    //Metodi da mettere su file a parte
    lista<type_elenco *> TextToList();
private slots:

    void tipologiaIndexChanged(int);
    void onTextChanged();
    void OnClick();
    void Aggiorna();

};

#endif // VIEW_ANNOTAZIONE_H
