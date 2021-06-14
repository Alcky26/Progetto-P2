#ifndef WANNOTAZIONE_H
#define WANNOTAZIONE_H

#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QGraphicsView>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QScrollBar>

#include "Data/annotazione.h"
#include "Data/nota.h"
#include "Data/ricorrenza.h"
#include "Data/promemoria.h"
#include "Data/elenco.h"
#include "Data/spesa.h"
#include "Model/model_annotazione.h"
#include "Util/metodi_extra.h"
#include "Util/lista.h"

class wAnnotazione : public QWidget
{
     Q_OBJECT
public:

    wAnnotazione(annotazione *ann, QWidget *parent = 0);
    ~wAnnotazione();

// Funzionalità di Clicked
protected:
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);

private:
    QVBoxLayout *_mainBoxLayout;
    QLabel *_LabTitolo;
    QPlainTextEdit  * _LabCorpo;
    QLabel *_LabDateTime;
    QLabel *_LabRicorrenza;
    QLabel *_LabDescrizione;
    QLabel *_LabCostoTot;
    QPlainTextEdit *_LabElenco;

    bool _state;

signals :
    void clicked();
    void released();
    void pressed();
};

#endif // WANNOTAZIONE_H
