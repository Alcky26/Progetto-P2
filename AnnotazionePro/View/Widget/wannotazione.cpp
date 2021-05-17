#include "wannotazione.h"

wAnnotazione::wAnnotazione(ModelAnnotazione *model, QWidget *parent) : QWidget(parent), _model(model)
{
    mainLayout= new QVBoxLayout(this);
    griglia = new QGridLayout();
    opzioni = new QVBoxLayout();

        _scelta = new QPushButton();
    _aggiungi = new QPushButton();

    viewAggiungi();
    //Modifica();

    mainLayout->setMargin(0);
    setLayout(mainLayout);

    mainLayout->addLayout(griglia,80);

    mainLayout->addLayout(opzioni,20);

}

void wAnnotazione::viewAggiungi()
{
    viewLayoutAggiungi = new QGridLayout();
    viewLayoutAggiungi->setColumnStretch(0,1);

    _tipologia = new QComboBox();
    _LineTitolo = new QLineEdit();
    _LineDescrizione = new QLineEdit();
    //_LineValori = new QLineEdit();

    //Azioni

    _aggiungi = new QPushButton("Aggiungi");

    //Tipo
    QVBoxLayout *tipologiaLayout = new QVBoxLayout();
    tipologiaLayout->setSpacing(0);
    tipologiaLayout->addWidget(new QLabel("Titolo"));

    //rip
    _tipologia->addItems(ModelAnnotazione::categorie());
    tipologiaLayout->addWidget(_tipologia);
    viewLayoutAggiungi->addLayout(tipologiaLayout, 0, 0);

}

/*void wAnnotazione::Modifica()
{

}*/

bool wAnnotazione::InputValido()
{
    return true;
}

void wAnnotazione::Reset()
{

}
