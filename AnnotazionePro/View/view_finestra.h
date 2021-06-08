#ifndef VIEW_FINESTRA_H
#define VIEW_FINESTRA_H

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
#include "View/view_annotazione.h"
#include "Util/lista.h"
#include "Util/type_elenco.h"
#include "Util/type_spesa.h"
#include "Util/metodo_tipo.h"

class view_finestra : public QWidget
{
    Q_OBJECT

public:
    view_finestra(model_annotazione* model, annotazione* ann, QWidget *parent = nullptr);
    ~view_finestra();

private:
    model_annotazione *_Model;
    annotazione *_ann;

    bool _StatoModifica;

    QVBoxLayout *_MainLayout;
    QGroupBox *_BoxTitolo,*_BoxDataOra,*_BoxCorpo,*_BoxDesc,*_BoxTable;
    //Elementi per Visualizzare
    QLineEdit *_LineTitolo;
    QTextEdit *_LineCorpo, *_LineDesc;
    QCalendarWidget *_calendario;
    QDateTimeEdit *_ora;
    QTableWidget *_TableList;
    QComboBox *_tipo;
    QPushButton *_BtnAddRow;
    QPushButton *_BtnLeft,*_BtnRight;
    QPushButton *_elimina,*_modifica;

    void SetAllEnabled(const bool _boolean);
    annotazione* ReadChangedValues() const;
    void closeEvent(QCloseEvent *event);

    void setupTitolo();
    void setupDataOra();
    void setupDescrizione();

signals:
    void AggiornaGriglia();
    void AggiornaGrigliaAlternativo(int i);
    void ClosedWindow();
    void SpostaSinLog(annotazione* a);
    void SpostaDesLog(annotazione* a);
    void ModificaLog(annotazione* a);
    void EliminaLog(annotazione* a);
private slots:
    void OnClickModifica();
    void OnClickElimina();
    void MoveWAnnLeft();
    void MoveWAnnRight();
    void AggiungiRiga();

};

#endif // VIEW_FINESTRA_H
