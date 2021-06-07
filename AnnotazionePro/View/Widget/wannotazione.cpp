#include "wannotazione.h"

wAnnotazione::wAnnotazione(annotazione *ann, QWidget *parent) : QWidget(parent)
{
    _mainBoxLayout = new QVBoxLayout(this);

    _state=0;

    QListWidget *_MainWidgetList= new QListWidget();
    _MainWidgetList->setSizeAdjustPolicy(QListWidget::AdjustToContents);

    QVBoxLayout *_mainVBoxLayout = new QVBoxLayout();

    //varia in base al tipo dynamico di ann
    QGroupBox *_Titolo = new QGroupBox();
    QVBoxLayout *_BoxTitle =new QVBoxLayout();


    _LabTitolo = new QLabel(ann->getTitolo());
    _LabTitolo->setAlignment(Qt::AlignCenter);
    _BoxTitle->addWidget(_LabTitolo);

    _Titolo->setLayout(_BoxTitle);
    _mainVBoxLayout->addWidget(_Titolo);


    if(dynamic_cast<promemoria*>(ann))
    {
        _LabDateTime = new QLabel("Data : "+dynamic_cast<promemoria*>(ann)->getDate().toString() + "\n"+"Ora : " +  dynamic_cast<promemoria*>(ann)->getTime().toString());
        _mainVBoxLayout->addWidget(_LabDateTime);
    }

    if(dynamic_cast<ricorrenza*>(ann))
    {
        _LabDateTime = new QLabel("Data : "+dynamic_cast<ricorrenza*>(ann)->getDate().toString() + "\n"+"Ora : " +  dynamic_cast<ricorrenza*>(ann)->getTime().toString());
        _mainVBoxLayout->addWidget(_LabDateTime);
        _LabRicorrenza = new QLabel(dynamic_cast<ricorrenza*>(ann)->typeToQString());
        _mainVBoxLayout->addWidget(_LabRicorrenza);
    }

    if(dynamic_cast<nota*>(ann))
    {
        _LabCorpo = new QPlainTextEdit(dynamic_cast<nota*>(ann)->getCorpo());
        _LabCorpo->setFrameStyle(1);
        _LabCorpo->setReadOnly(true);
        _LabCorpo->setVerticalScrollBar(new QScrollBar());
        _LabCorpo->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _LabCorpo->setStyleSheet("background:rgb(224, 217, 215);");
        _mainVBoxLayout->addWidget(_LabCorpo);
    }

    if(dynamic_cast<elenco*>(ann) && !dynamic_cast<spesa*>(ann))
    {
        _LabDescrizione = new QLabel(dynamic_cast<elenco*>(ann)->getDescrizione());
        _mainVBoxLayout->addWidget(_LabDescrizione);
        _LabElenco = new QPlainTextEdit (metodi_extra::ElencoAsText(dynamic_cast<elenco*>(ann)->getElenco()));
        _LabElenco->setFrameStyle(1);
        _LabElenco->setReadOnly(true);
        _LabElenco->setVerticalScrollBar(new QScrollBar());
        _LabElenco->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _LabElenco->setStyleSheet("background:rgb(224, 217, 215);");
        _mainVBoxLayout->addWidget(_LabElenco);
    }

    if(dynamic_cast<spesa*>(ann))
    {
        _LabDescrizione = new QLabel(dynamic_cast<spesa*>(ann)->getDescrizione());  
        _mainVBoxLayout->addWidget(_LabDescrizione);
        _LabElenco = new QPlainTextEdit(metodi_extra::SpesaAsText(dynamic_cast<spesa*>(ann)->getSpesa() ));
        _LabElenco->setFrameStyle(1);
        _LabElenco->setReadOnly(true);
        _LabElenco->setVerticalScrollBar(new QScrollBar());
        _LabElenco->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _LabElenco->setStyleSheet("background:rgb(224, 217, 215);");
        _mainVBoxLayout->addWidget(_LabElenco);
    }

    _MainWidgetList->setLayout(_mainVBoxLayout);

    _mainBoxLayout->addWidget(_MainWidgetList);

}

wAnnotazione::~wAnnotazione()
{
    delete _mainBoxLayout;
}

void wAnnotazione::mousePressEvent(QMouseEvent *)
{
    _state = 1;
    repaint();
    emit pressed();
}

void wAnnotazione::mouseReleaseEvent(QMouseEvent *)
{
    _state = 0;
    repaint();
    emit released();
    emit clicked();
}

void wAnnotazione::paintEvent(QPaintEvent *)
{
    if(_state)
    {
        _state=0;
        update();
    }
    else
    {
        _state=1;
        update();
    }
}

