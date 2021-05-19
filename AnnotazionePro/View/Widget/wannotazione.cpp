#include "wannotazione.h"

wAnnotazione::wAnnotazione(ModelAnnotazione *model, QWidget *parent) : QWidget(parent), _model(model)
{
    mainLayout= new QHBoxLayout(this);
    griglia = new QVBoxLayout();
    opzioni = new QVBoxLayout();

    spacingOpzioni = new QGroupBox("Opzioni");
    spacingGriglia = new QGroupBox("Griglia");

    _scelta = new QPushButton();
    _aggiungi = new QPushButton();

    /*QSizePolicy aggiungiPolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    aggiungiPolicy.setHorizontalStretch(4);
    spacingOpzioni->setSizePolicy(aggiungiPolicy);

    QSizePolicy aggiungiPolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
    aggiungiPolicy2.setHorizontalStretch(3);
    spacingGriglia->setSizePolicy(aggiungiPolicy2);*/

    //Modifica();

    viewAggiungi();

    ///////GRIGLIA

    viewLayoutGriglia = new QGridLayout();

    spacingGriglia->setLayout(viewLayoutGriglia);
    griglia->addWidget(spacingGriglia);

    /////////////

    mainLayout->addLayout(griglia,80);
    mainLayout->addLayout(opzioni,20);

    mainLayout->setMargin(0);
    setLayout(mainLayout);

    connect(_tipologia, SIGNAL(currentIndexChanged(int)), this, SLOT(tipologiaIndexChanged(int)));

}

void wAnnotazione::viewAggiungi()
{
    viewLayoutAggiungi = new QVBoxLayout();
    viewLayoutAggiungi->setSpacing(0);

    _LineTitolo = new QLineEdit();
    _LineCorpo = new QLineEdit();

    _tipologia = new QComboBox();

    //Azioni

    _aggiungi = new QPushButton("Aggiungi");

    //Tipolog
    QVBoxLayout *tipologiaLayout = new QVBoxLayout();
    tipologiaLayout->setSpacing(0);
    tipologiaLayout->addWidget(new QLabel("Tipologia"));
    _tipologia->addItems(ModelAnnotazione::categorie());
    tipologiaLayout->addWidget(_tipologia,1,Qt::AlignTop);
    viewLayoutAggiungi->addLayout(tipologiaLayout);

    //ANNOTAZIONE
    layoutAnnotazione = new QVBoxLayout();
    layoutAnnotazione->setSpacing(0);
    _LineTitolo->setPlaceholderText("Titolo");
    layoutAnnotazione->addWidget(_LineTitolo,1);

    //NOTA
    _LineCorpo->setPlaceholderText("Corpo");
    layoutAnnotazione->addWidget(_LineCorpo,1);



    viewLayoutAggiungi->addLayout(layoutAnnotazione);



    spacingOpzioni->setLayout(viewLayoutAggiungi);
    opzioni->addWidget(spacingOpzioni);
}

void wAnnotazione::VisualizzaNota()
{
    _LineCorpo->setVisible(true);
}

void wAnnotazione::VisualizzaPromemoria()
{
    _LineCorpo->setVisible(false);
}

void wAnnotazione::VisualizzaRicorrenza()
{
    _LineCorpo->setVisible(false);
}

void wAnnotazione::VisualizzaElenco()
{
    _LineCorpo->setVisible(false);
}

void wAnnotazione::VisualizzaSpesa()
{
    _LineCorpo->setVisible(false);
}

/*void wAnnotazione::Modifica()
{

}*/

void wAnnotazione::tipologiaIndexChanged(int index)
{
    if(index==0)
        VisualizzaNota();
    else if (index == 1)
        VisualizzaPromemoria();
    else if (index == 2)
        VisualizzaRicorrenza();
    else if (index == 3)
        VisualizzaElenco();
    else if (index == 4)
        VisualizzaSpesa();
}

bool wAnnotazione::InputValido()
{
    return true;
}

void wAnnotazione::Reset()
{

}
