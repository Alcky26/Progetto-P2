#include "view_annotazione.h"



view_annotazione::view_annotazione(model_annotazione *model, QWidget *parent): QWidget(parent), _model(model)
{
    _mainLayout = new QHBoxLayout(this);
    _griglia = new QVBoxLayout();
    _opzioni = new QVBoxLayout();

    // Setup Opzioni
    viewOpzioni();
    // Setup Griglia
    viewGriglia();

    _mainLayout->addLayout(_griglia,70);
    _mainLayout->addLayout(_opzioni,30);

    connect(_tipologia, SIGNAL(currentIndexChanged(int)), this, SLOT(tipologiaIndexChanged(int)));
    connect(_LineCorpo, SIGNAL(textChanged()), this, SLOT( onTextChanged() ) );


    connect(_aggiunta, SIGNAL(clicked()), this, SLOT(OnClick()));
}

void view_annotazione::viewOpzioni()
{

    QVBoxLayout *_tempLayoutOpzioni = new QVBoxLayout();
    QGroupBox *suppLayoutOpzioni = new QGroupBox("Opzioni");

    _LineTitolo = new QLineEdit();
    _LineCorpo = new QTextEdit();
    _tipologia = new QComboBox();
    _calendario = new QCalendarWidget();

    _tempLayoutOpzioni->addWidget(new QLabel("Tipologia"));
    _tipologia->addItems(model_annotazione::categorie());
    _tipologia->setMaximumWidth(500);
    _tempLayoutOpzioni->addWidget(_tipologia);


    _LineTitolo->setPlaceholderText("Titolo");
    _LineTitolo->setMaximumWidth(500);
    _tempLayoutOpzioni->addWidget(_LineTitolo);

    //NOTA
    _LineCorpo->setPlaceholderText("Corpo");
    _LineCorpo->setMaximumWidth(500);
    _LineCorpo->setMaximumHeight(23);
    _tempLayoutOpzioni->addWidget(_LineCorpo);

    ////
    _ora = new QDateTimeEdit(QDate::currentDate());
    _ora->setDisplayFormat("hh:mm:ss");
    _ora->setMaximumWidth(500);
    _tempLayoutOpzioni->addWidget(_ora);
    _ora->setVisible(false);
    ////

    _calendario->setMaximumWidth(500);
    _calendario->setGridVisible(true);
    _tempLayoutOpzioni->addWidget(_calendario);
    _calendario->setVisible(false);

    _aggiunta = new QPushButton("Aggiungi Nuova Annotazione");
    _aggiunta->setMaximumWidth(500);
    _tempLayoutOpzioni->addWidget(_aggiunta);

    suppLayoutOpzioni->setLayout(_tempLayoutOpzioni);
    suppLayoutOpzioni->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);

    _opzioni->addWidget(suppLayoutOpzioni);
    _opzioni->setAlignment(suppLayoutOpzioni,Qt::AlignTop);
}

void view_annotazione::onTextChanged()
{
    QSize size = _LineCorpo->document()->size().toSize();
    _LineCorpo->setFixedHeight( size.height() + 3 );
}

void view_annotazione::viewGriglia()
{
     _tempLayoutGriglia = new QGridLayout();
    _suppLayoutGriglia = new QGraphicsView();

    /*QSizePolicy suppPolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    suppPolicy.setHorizontalStretch(4);
    suppLayout->setSizePolicy(suppPolicy);*/

    clearGriglia();

    aggiornaGriglia(_tempLayoutGriglia);

    _suppLayoutGriglia->setLayout(_tempLayoutGriglia);
    _griglia->addWidget(_suppLayoutGriglia);
}

void view_annotazione::clearGriglia()
{
    for (int i = 0; i < _griglia->count(); i++)
    {
       _griglia->itemAt(i)->widget()->deleteLater();
    }
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
    _ora->setVisible(false);
    _calendario->setVisible(false);
}

void view_annotazione::VisualizzaPromemoria()
{
    _LineCorpo->setVisible(true);
    _ora->setVisible(true);
    _calendario->setVisible(true);
}

void view_annotazione::VisualizzaRicorrenza()
{
    _LineCorpo->setVisible(true);
    _ora->setVisible(true);
    _calendario->setVisible(true);
}

void view_annotazione::VisualizzaElenco()
{
    _LineCorpo->setVisible(false);
    _ora->setVisible(false);
    _calendario->setVisible(false);
}

void view_annotazione::VisualizzaSpesa()
{
    _LineCorpo->setVisible(false);
    _ora->setVisible(false);
    _calendario->setVisible(false);
}

void view_annotazione::aggiornaGriglia(QGridLayout *supplay)
{
    lista<wAnnotazione*> supp = _wA;
    int count = 0;
    for(lista<wAnnotazione*>::constiterator cit = supp.begin(); cit != supp.end(); cit++)
    {
        supplay->addWidget(*cit,  (count > 3) ? count/4 : 0, (count > 3) ? count-4*(count/4) : count);
        count++;
    }
}

void view_annotazione::OnClick()
{
    //if per tipologia
    annotazione *nuovo=nullptr;
    nuovo = new nota(_LineTitolo->text(), _LineCorpo->document()->toRawText());
    wAnnotazione *waa = new wAnnotazione(nuovo);
    _wA.insertFront(waa);
    waa->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Maximum);
    waa->setMaximumWidth(400);
    viewGriglia();
}
