#ifndef WANNOTAZIONE_H
#define WANNOTAZIONE_H

#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "Util/lista.h"
#include <QPushButton>
#include <QComboBox>
#include "Model/model_annotazione.h"
#include <QGroupBox>
#include "Data/annotazione.h"
#include "Data/nota.h"
#include "Data/ricorrenza.h"
#include "Data/promemoria.h"
#include "Data/elenco.h"
#include "Data/spesa.h"
#include <QGraphicsView>
#include <QListWidget>
#include <QPlainTextEdit >

class wAnnotazione : public QWidget
{
     Q_OBJECT
public:

    wAnnotazione(annotazione *ann, QWidget *parent = 0);
    ~wAnnotazione() = default;

private:
    QVBoxLayout *_mainBoxLayout;
    //QLabel *_LabTitolo, *_LabCorpo;
    QLabel *_LabTitolo;
    QPlainTextEdit  * _LabCorpo;
    QLabel *_LabDateTime;
    QLabel *_LabRicorrenza;
};

#endif // WANNOTAZIONE_H
