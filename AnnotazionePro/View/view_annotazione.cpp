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

    connect(_aggiorna,SIGNAL(clicked()), this, SLOT(Aggiorna()));
}

void view_annotazione::viewOpzioni()
{

    QVBoxLayout *_tempLayoutOpzioni = new QVBoxLayout();
    QGroupBox *suppLayoutOpzioni = new QGroupBox("Opzioni");

    _LineTitolo = new QLineEdit();
    _LineCorpo = new QTextEdit();
    _tipologia = new QComboBox();
    _calendario = new QCalendarWidget();
    _tipo = new QComboBox();

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

    //ORA
    _ora = new QDateTimeEdit(QDate::currentDate());
    _ora->setDisplayFormat("hh:mm:ss");
    _ora->setMaximumWidth(500);
    _tempLayoutOpzioni->addWidget(_ora);
    _ora->setVisible(false);

    //DATA
    _calendario->setMaximumWidth(500);
    _calendario->setGridVisible(true);
    _tempLayoutOpzioni->addWidget(_calendario);
    _calendario->setVisible(false);

    //TIPO
    _tipo->addItem("Giornaliero");
    _tipo->addItem("Settimanale");
    _tipo->addItem("Mensile");
    _tipo->addItem("Annuale");
    _tempLayoutOpzioni->addWidget(_tipo);
    _tipo->setVisible(false);

    //LISTA per LIST
    _ListHelp = new QLabel("Separare i valori dell'array con ;");
    _LineList = new QTextEdit();
    _LineList->setMaximumWidth(500);
    _ListHelp->setVisible(false);
    _LineList->setVisible(false);
    _tempLayoutOpzioni->addWidget(_ListHelp);
    _tempLayoutOpzioni->addWidget(_LineList);

    //BOTTONE 1 ( AGGIUNGI )
    _aggiunta = new QPushButton("Aggiungi Nuova Annotazione");
    _aggiunta->setMaximumWidth(500);
    _tempLayoutOpzioni->addWidget(_aggiunta);

    //BOTTONE 2 ( AGGIORNA )
    _aggiorna = new QPushButton("Aggiorna");
    _tempLayoutOpzioni->addWidget(_aggiorna);
    _aggiorna->setMaximumWidth(500);

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
    QGridLayout *_tempLayoutGriglia = new QGridLayout();
    QGroupBox *_suppLayoutGriglia = new QGroupBox();

    /*QSizePolicy suppPolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    suppPolicy.setHorizontalStretch(4);
    _suppLayoutGriglia->setSizePolicy(suppPolicy);*/

    QScrollArea *_scrollAreaAnnot = new QScrollArea;


    clearGriglia();

    QRect geometry = _griglia->geometry();
    int width = geometry.width();


    //////////////////////////////////////
    /*
    WIDTH 100
    SP - T - SP - T - SP - T - SP - T - SP
    5 * SP + 4 * T = 100
    20 (T) * 4 + X (SP) * 5 = 100
    5 * X = 28
    T è 20
    SP è 4
    */
    /////////////////////////////////////
    _tempLayoutGriglia->setSpacing(width/25);

    aggiornaGriglia(_tempLayoutGriglia);

    _suppLayoutGriglia->setLayout(_tempLayoutGriglia);
    _scrollAreaAnnot->setWidget(_suppLayoutGriglia);
    _griglia->addWidget(_scrollAreaAnnot);

}

void view_annotazione::clearGriglia()
{
    for (int i = 0; i < _griglia->count(); i++)
    {
       _griglia->itemAt(i)->widget()->deleteLater();
    }
}

void view_annotazione::resizeAnn(wAnnotazione* Ann)
{
    QRect geometry = _griglia->geometry();
    int width = geometry.width();
    int height = geometry.height();
    Ann->setMaximumSize(width/5,height/5);
    Ann->setFixedSize(width/5,height/5);
    Ann->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
}

Tipo view_annotazione::MetodoSupporto(int _index)
{
    Tipo _nuovoTipo=Giornaliero;
    if(_index==0)
        _nuovoTipo = Giornaliero;
    else if (_index == 1)
        _nuovoTipo = Settimanale;
    else if (_index == 2)
       _nuovoTipo = Mensile;
    else if (_index == 3)
       _nuovoTipo = Annuale;

    return _nuovoTipo;
}

lista<type_elenco *> view_annotazione::TextToList()
{

    QString _BoxValue=_LineList->document()->toRawText();
    QStringList _SupportList = _BoxValue.split(';');
    lista<type_elenco*> _endResult;

    for(QStringList::ConstIterator cit=_SupportList.begin(); cit != _SupportList.end(); cit++)
    {

        _endResult.insertFront(new type_elenco(* (cit),false));
    }

    return _endResult;
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
    _tipo->setVisible(false);
    _LineList->setVisible(false);
    _ListHelp->setVisible(false);
}

void view_annotazione::VisualizzaPromemoria()
{
    _LineCorpo->setVisible(true);
    _ora->setVisible(true);
    _calendario->setVisible(true);
    _tipo->setVisible(false);
    _LineList->setVisible(false);
    _ListHelp->setVisible(false);
}

void view_annotazione::VisualizzaRicorrenza()
{
    _LineCorpo->setVisible(true);
    _ora->setVisible(true);
    _calendario->setVisible(true);
    _tipo->setVisible(true);
    _LineList->setVisible(false);
    _ListHelp->setVisible(false);
}

void view_annotazione::VisualizzaElenco()
{
    _LineCorpo->setVisible(true);
    _ora->setVisible(false);
    _calendario->setVisible(false);
    _tipo->setVisible(false);
    _LineList->setVisible(true);
    _ListHelp->setVisible(true);
}

void view_annotazione::VisualizzaSpesa()
{
    _LineCorpo->setVisible(true);
    _ora->setVisible(false);
    _calendario->setVisible(false);
    _tipo->setVisible(false);
    _LineList->setVisible(true);
    _ListHelp->setVisible(true);
}

void view_annotazione::aggiornaGriglia(QGridLayout *supplay)
{

    lista<wAnnotazione*> supp = _wA;
    int count = 0;
    for(lista<wAnnotazione*>::constiterator cit = supp.begin(); cit != supp.end(); cit++)
    {
        resizeAnn(* cit);
        supplay->addWidget(*cit,  (count > 3) ? count/4 : 0, (count > 3) ? count-4*(count/4) : count);
        count++;
    }
    supplay->setAlignment(Qt::AlignLeft);
    supplay->setAlignment(Qt::AlignTop);
}

void view_annotazione::OnClick()
{
    //if per tipologia
    int _value = _tipologia->currentIndex();
    annotazione *_nuovoInsert =nullptr;
    //Nota
    if(_value==0)
        _nuovoInsert  = new nota(_LineTitolo->text(), _LineCorpo->document()->toRawText());
    //Promemoria
    else if (_value == 1)
        _nuovoInsert  = new promemoria(_LineTitolo->text(), _LineCorpo->document()->toRawText(),_calendario->selectedDate(),_ora->time());
    //Ricorrenza
    else if (_value == 2)
        //Cambiare Giornaliero con l'effettivo tipo
        _nuovoInsert  = new ricorrenza(_LineTitolo->text(), _LineCorpo->document()->toRawText(),_calendario->selectedDate(),_ora->time(), MetodoSupporto(_tipo->currentIndex()));
    //Elenco
    else if (_value == 3)
        // Fix later Lol
        //_nuovoInsert  = new elenco(_LineTitolo->text(), _LineCorpo->document()->toRawText(), TextToList());
        //_nuovoInsert  = new elenco(_LineTitolo->text(), _LineCorpo->document()->toRawText());
        _nuovoInsert = new elenco("a","b",TextToList());
    //Spesa
    else if (_value == 4)
        //Fix Later Lol
        _nuovoInsert  = new spesa(_LineTitolo->text(), _LineCorpo->document()->toRawText());

    //annotazione *_nuovoInsert =nullptr;

    wAnnotazione *_nuovoWAnn = new wAnnotazione(_nuovoInsert );
    _wA.insertFront(_nuovoWAnn);
    viewGriglia();
}

void view_annotazione::Aggiorna()
{
    viewGriglia();
}


