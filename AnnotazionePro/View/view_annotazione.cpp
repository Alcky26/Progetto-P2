#include "view_annotazione.h"



view_annotazione::view_annotazione(model_annotazione *model, QWidget *parent): QWidget(parent), _model(model)
{
    mainLayout = new QHBoxLayout(this);
    griglia = new QVBoxLayout();
    opzioni = new QVBoxLayout();

    viewOpzioni();

    mainLayout->addLayout(griglia,80);
    mainLayout->addLayout(opzioni,20);

    connect(_tipologia, SIGNAL(currentIndexChanged(int)), this, SLOT(tipologiaIndexChanged(int)));
}

void view_annotazione::viewOpzioni()
{
    QVBoxLayout *tempLayout = new QVBoxLayout();
    QGroupBox *suppLayout = new QGroupBox("Griglia");

    /*QSizePolicy suppPolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    suppPolicy.setHorizontalStretch(4);
    suppLayout->setSizePolicy(suppPolicy);*/

    suppLayout->setLayout(tempLayout);
    griglia->addWidget(suppLayout);

    QVBoxLayout *tempLayout2 = new QVBoxLayout();
    QGroupBox *suppLayout2 = new QGroupBox("Opzioni");

    _LineTitolo = new QLineEdit();
    _LineCorpo = new QLineEdit();
    _tipologia = new QComboBox();
    _calendario = new QCalendarWidget();

    tempLayout2->addWidget(new QLabel("Tipologia"));
    _tipologia->addItems(model_annotazione::categorie());
    tempLayout2->addWidget(_tipologia);


    _LineTitolo->setPlaceholderText("Titolo");
    tempLayout2->addWidget(_LineTitolo);

    //NOTA
    _LineCorpo->setPlaceholderText("Corpo");
    tempLayout2->addWidget(_LineCorpo);

    tempLayout2->addWidget(_calendario);
    _calendario->setVisible(false);

    ////
    _ora = new QDateTimeEdit(QDate::currentDate());
    _ora->setMinimumDate(QDate::currentDate().addDays(-365));
    _ora->setMaximumDate(QDate::currentDate().addDays(365));
    _ora->setDisplayFormat("yyyy.MM.dd");
    tempLayout2->addWidget(_ora);

    ////

    suppLayout2->setLayout(tempLayout2);
    suppLayout2->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);

    opzioni->addWidget(suppLayout2);
    opzioni->setAlignment(suppLayout2,Qt::AlignTop);
}


void view_annotazione::tipologiaIndexChanged(int index)
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

void view_annotazione::VisualizzaNota()
{
    _LineCorpo->setVisible(true);
    _calendario->setVisible(false);
}

void view_annotazione::VisualizzaPromemoria()
{
    _LineCorpo->setVisible(true);
    _calendario->setVisible(true);
}

void view_annotazione::VisualizzaRicorrenza()
{
    _LineCorpo->setVisible(true);
    _calendario->setVisible(true);
}

void view_annotazione::VisualizzaElenco()
{
    _LineCorpo->setVisible(false);
    _calendario->setVisible(false);
}

void view_annotazione::VisualizzaSpesa()
{
    _LineCorpo->setVisible(false);
    _calendario->setVisible(false);
}
