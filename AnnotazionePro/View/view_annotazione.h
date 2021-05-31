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
#include <QTableWidget>
#include "Util/metodi_extra.h"
#include <QSignalMapper>
#include "view_finestra.h"
#include <QCheckBox>
#include <QRadioButton>

class view_annotazione : public QWidget
{
    Q_OBJECT
public:
    // Costruttore
    view_annotazione(model_annotazione *model, QWidget *parent = 0);
    ~view_annotazione();

    void viewGriglia();
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
    QTextEdit *_LineCorpo, *_LineDesc;
    QComboBox *_tipologia;   
    QCalendarWidget *_calendario;
    QDateTimeEdit *_ora;
    QComboBox *_tipo;

    QTableWidget *_TableList;

    QSignalMapper *_SignalMapper;

    QPushButton *_aggiunta;
    QPushButton *_aggiungiRiga;
    QPushButton *_svuotaGriglia;

    QCheckBox *_checkAnn,*_checkProm,*_checkRic,*_checkEle,*_checkSpes;

    // Metodi
    void viewOpzioni();


    void VisualizzaNota();
    void VisualizzaPromemoria();
    void VisualizzaRicorrenza();
    void VisualizzaElenco();
    void VisualizzaSpesa();


    void aggiornaGriglia(QGridLayout *supplay);
    void resizeAnn(wAnnotazione* Ann);
    void aggiornaValoriGriglia();
    void AggiornaConFiltro();
    void AggiornaConOrdinamento();

    void AggiuntaAnnotazione();

    void SetSignalMapper(wAnnotazione *_wAnn);
    void resizeEvent(QResizeEvent *event);

    void clearGriglia();

private slots:
    void dumpGriglia();
    void SetGrigliaEnabled();
    void Aggiorna();
    void tipologiaIndexChanged(int);
    void onTextChanged();
    void OnClick();
    void OnClickRow();
    void ShowDettagli( int);

};

#endif // VIEW_ANNOTAZIONE_H
