#include "wannotazione.h"

wAnnotazione::wAnnotazione(annotazione *ann, QWidget *parent) : QWidget(parent)
{
    _mainBoxLayout = new QVBoxLayout(this);

    QListWidget *scatola= new QListWidget();
    scatola->setSizeAdjustPolicy(QListWidget::AdjustToContents);

    QVBoxLayout *temp = new QVBoxLayout();

    //varia in base al tipo dynamico di ann
    _LabTitolo = new QLabel(ann->getTitolo());
    //_LabCorpo = new QLabel(dynamic_cast<nota*>(ann)->getCorpo());
    _LabCorpo = new QPlainTextEdit (dynamic_cast<nota*>(ann)->getCorpo());
    temp->addWidget(_LabTitolo);

    temp->addWidget(_LabCorpo);

    if(dynamic_cast<promemoria*>(ann))
    {
        _LabDateTime = new QLabel(dynamic_cast<promemoria*>(ann)->getDate().toString() + " " +  dynamic_cast<promemoria*>(ann)->getTime().toString());
        temp->addWidget(_LabDateTime);
    }

    if(dynamic_cast<ricorrenza*>(ann))
    {
        _LabDateTime = new QLabel(dynamic_cast<ricorrenza*>(ann)->getDate().toString());

        temp->addWidget(_LabDateTime);
    }


    /*if(dynamic_cast<ricorrenza*>(ann))
    {
        _LabDateTime = new QLabel(dynamic_cast<ricorrenza*>(ann)->getDate().toString() + " " + dynamic_cast<promemoria*>(ann)->getTime().toString());
        temp->addWidget(_LabDateTime);


        //_LabRicorrenza = new QLabel(dynamic_cast<ricorrenza*>(ann)->typeToQString());
        //temp->addWidget(_LabRicorrenza);
    }*/

    scatola->setLayout(temp);
    _mainBoxLayout->addWidget(scatola);
}
