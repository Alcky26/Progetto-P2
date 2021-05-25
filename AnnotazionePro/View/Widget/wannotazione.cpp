#include "wannotazione.h"

wAnnotazione::wAnnotazione(annotazione *ann, QWidget *parent) : QWidget(parent)
{
    _mainBoxLayout = new QVBoxLayout(this);

    setAttribute(Qt::WA_Hover);


    QListWidget *_Scatola= new QListWidget();
    _Scatola->setSizeAdjustPolicy(QListWidget::AdjustToContents);
    _Scatola->setStyleSheet("color:white;background-color:rgb(50, 168, 82);");

    QVBoxLayout *_mainVBoxLayout = new QVBoxLayout();

    QFont _TitleFont("Times", 15, QFont::Bold);
    QFont _MainFont("Times", 12);

    //varia in base al tipo dynamico di ann
    _LabTitolo = new QLabel(ann->getTitolo());
    _LabTitolo->setFont(_TitleFont);
    _mainVBoxLayout->addWidget(_LabTitolo);


    if(dynamic_cast<promemoria*>(ann))
    {
        _LabDateTime = new QLabel("Data : "+dynamic_cast<promemoria*>(ann)->getDate().toString() + "\n"+"Ora : " +  dynamic_cast<promemoria*>(ann)->getTime().toString());
        _mainVBoxLayout->addWidget(_LabDateTime);
        _LabDateTime->setFont(_MainFont);
        _Scatola->setStyleSheet("color:white;background-color:rgb(50, 97, 168);");
    }

    if(dynamic_cast<ricorrenza*>(ann))
    {
        _LabDateTime = new QLabel("Data : "+dynamic_cast<ricorrenza*>(ann)->getDate().toString() + "\n"+"Ora : " +  dynamic_cast<ricorrenza*>(ann)->getTime().toString());
        _mainVBoxLayout->addWidget(_LabDateTime);
        _LabDateTime->setFont(_MainFont);
        _LabRicorrenza = new QLabel(dynamic_cast<ricorrenza*>(ann)->typeToQString());
        _mainVBoxLayout->addWidget(_LabRicorrenza);
        _LabRicorrenza->setFont(_MainFont);
        _Scatola->setStyleSheet("color:white;background-color:rgb(214, 125, 24);");
    }

    if(dynamic_cast<nota*>(ann))
    {
        _LabCorpo = new QPlainTextEdit(dynamic_cast<nota*>(ann)->getCorpo());
        _LabCorpo->setFont(_MainFont);
        _LabCorpo->setFrameStyle(1);
        _LabCorpo->setEnabled(false);
        _LabCorpo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        _corpoScroll=new QScrollArea();
        //_corpoScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        _corpoScroll->setWidget(_LabCorpo);
        _mainVBoxLayout->addWidget(_corpoScroll);
    }

    if(dynamic_cast<elenco*>(ann) && !dynamic_cast<spesa*>(ann))
    {
        _LabDescrizione = new QLabel(dynamic_cast<elenco*>(ann)->getDescrizione());
        _mainVBoxLayout->addWidget(_LabDescrizione);
        _LabDescrizione->setFont(_MainFont);
        _LabElenco = new QPlainTextEdit (dynamic_cast<elenco*>(ann)->getListAsText());
        _LabElenco->setFont(_MainFont);
        _LabElenco->setFrameStyle(1);
        _LabElenco->setEnabled(false);
        _LabElenco->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        _corpoScroll=new QScrollArea();
        _corpoScroll->setWidget(_LabElenco);
        _mainVBoxLayout->addWidget(_corpoScroll);
        _Scatola->setStyleSheet("color:white;background-color:rgb(212, 16, 222);");
    }

    if(dynamic_cast<spesa*>(ann))
    {
        _LabDescrizione = new QLabel(dynamic_cast<spesa*>(ann)->getDescrizione());
        _mainVBoxLayout->addWidget(_LabDescrizione);
        _LabDescrizione->setFont(_MainFont);
        _LabElenco = new QPlainTextEdit(dynamic_cast<spesa*>(ann)->getListSpesaAsText());
        _LabElenco->setFont(_MainFont);
        _LabElenco->setEnabled(false);
        _LabElenco->setFrameStyle(1);
        _LabElenco->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        _corpoScroll=new QScrollArea();
        _corpoScroll->setWidget(_LabElenco);
        _mainVBoxLayout->addWidget(_corpoScroll);
        _Scatola->setStyleSheet("color:white;background-color:rgb(237, 5, 9);");
    }

    _Scatola->setLayout(_mainVBoxLayout);
    //_Scatola->setStyleSheet("color:white;background-color:rgb(176, 203, 247);");
    _mainBoxLayout->addWidget(_Scatola);

}





