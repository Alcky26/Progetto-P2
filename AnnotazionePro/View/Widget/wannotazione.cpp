#include "wannotazione.h"

wAnnotazione::wAnnotazione(annotazione *ann, QWidget *parent) : QWidget(parent)
{
    _mainBoxLayout = new QVBoxLayout(this);

    QListWidget *scatola= new QListWidget();
    scatola->setSizeAdjustPolicy(QListWidget::AdjustToContents);

    QVBoxLayout *temp = new QVBoxLayout();

    //varia in base al tipo dynamico di ann
    _LabTitolo = new QLabel(ann->getTitolo());
    _LabCorpo = new QLabel(dynamic_cast<nota*>(ann)->getCorpo());
    temp->addWidget(_LabTitolo);
    temp->addWidget(_LabCorpo);

    scatola->setLayout(temp);
    _mainBoxLayout->addWidget(scatola);
}
