#include "wannotazione.h"

wAnnotazione::wAnnotazione(annotazione *ann, QWidget *parent) : QWidget(parent)
{
    _mainBoxLayout = new QVBoxLayout(this);

    QListWidget *_Scatola= new QListWidget();
    _Scatola->setSizeAdjustPolicy(QListWidget::AdjustToContents);

    QVBoxLayout *_mainVBoxLayout = new QVBoxLayout();

    //varia in base al tipo dynamico di ann
    _LabTitolo = new QLabel(ann->getTitolo());
    _mainVBoxLayout->addWidget(_LabTitolo);

    _LabCorpo = new QPlainTextEdit (dynamic_cast<nota*>(ann)->getCorpo());
    _mainVBoxLayout->addWidget(_LabCorpo);

    //_LabCorpo = new QLabel(dynamic_cast<nota*>(ann)->getCorpo());


    if(dynamic_cast<promemoria*>(ann))
    {
        _LabDateTime = new QLabel(dynamic_cast<promemoria*>(ann)->getDate().toString() + " " +  dynamic_cast<promemoria*>(ann)->getTime().toString());
        _mainVBoxLayout->addWidget(_LabDateTime);
    }

    if(dynamic_cast<ricorrenza*>(ann))
    {
        _LabDateTime = new QLabel(dynamic_cast<ricorrenza*>(ann)->getDate().toString()+ " " +dynamic_cast<ricorrenza*>(ann)->getTime().toString());
        _mainVBoxLayout->addWidget(_LabDateTime);
        _LabRicorrenza = new QLabel(dynamic_cast<ricorrenza*>(ann)->typeToQString());
        _mainVBoxLayout->addWidget(_LabRicorrenza);
    }
/*
    if(dynamic_cast<elenco*>(ann))
    {
        _LabElenco = new QLabel(dynamic_cast<elenco*>(ann)->getListAsText());
        _mainVBoxLayout->addWidget(_LabDateTime);
    }
*/
    _Scatola->setLayout(_mainVBoxLayout);
    //_Scatola->setStyleSheet("color:white;background-color:rgb(176, 203, 247);");
    _mainBoxLayout->addWidget(_Scatola);
}
