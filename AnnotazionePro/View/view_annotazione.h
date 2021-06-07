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
#include <QGraphicsItem>
#include <QHeaderView>

class view_annotazione : public QWidget
{
    Q_OBJECT
public:
    // Costruttore
    view_annotazione(model_annotazione *model, QWidget *parent = 0);
    ~view_annotazione();

    void ApriGriglia();
private:

    // Modello
    model_annotazione *_Model;
    // Lista di Widget wAnnotazione
    lista<wAnnotazione*> _wA;

    // GUI
    QHBoxLayout *_MainLayout;

    // 2 Aree Principali
    QVBoxLayout *_InsertAndOptions;
    QVBoxLayout *_Grid;


    QScrollArea *_scrollAreaAnnot;

    //Elementi per Inserimento
    QLineEdit *_LineTitolo;
    QTextEdit *_LineCorpo, *_LineDesc, *_LineLog;
    QComboBox *_Tipologia;
    QCalendarWidget *_Calendario;
    QDateTimeEdit *_Ora;
    QComboBox *_Ricorrenza;
    QTableWidget *_TableList;
    // Mapper per Lista di Widget
    QSignalMapper *_SignalMapper;

    // Bottoni
    QPushButton *_BtnAdd, *_BtnAddRow, *_BtnDeleteGrid;

    // Metodi
    void viewOpzioni();
    void viewGriglia();
    void resizeAnn(wAnnotazione* Ann);
    void SetSignalMapper(wAnnotazione *_wAnn);
    void resizeEvent(QResizeEvent *event);

private slots:
    void OnClickBtnAggiungi();
    void UpdateGrid();
    void OnClickRow();
    void ComboBoxTypeChanged(int);
    void OnTextChanged();
    void DeleteGrid();
    void GridEnable();
    void OpenWindowDetails( int);
    void viewGrigliaAlternativo(int i);
    void SpostaSinistra(annotazione* a);
    void SpostaDestra(annotazione* a);
    void ModificaScrivi(annotazione* a);
    void EliminaScrivi(annotazione* a);
};

#endif // VIEW_ANNOTAZIONE_H
