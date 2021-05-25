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
    connect(_LineDesc, SIGNAL(textChanged()), this, SLOT( onTextChanged() ) );
    //Bottone
    connect(_aggiunta, SIGNAL(clicked()), this, SLOT(OnClick()));
    connect(_aggiorna,SIGNAL(clicked()), this, SLOT(Aggiorna()));
    connect(_aggiungiRiga,SIGNAL(clicked()), this, SLOT(OnClickRow()));

}

void view_annotazione::viewOpzioni()
{

    QVBoxLayout *_tempLayoutOpzioni = new QVBoxLayout();
    QGroupBox *suppLayoutOpzioni = new QGroupBox("Opzioni");

    _LineTitolo = new QLineEdit();
    _LineCorpo = new QTextEdit();
    _LineDesc = new QTextEdit();
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

    //DESCRIZIONE
    _LineDesc->setPlaceholderText("Descrizione");
    _LineDesc->setMaximumWidth(500);
    _LineDesc->setMaximumHeight(23);
    _tempLayoutOpzioni->addWidget(_LineDesc);
    _LineDesc->setVisible(false);

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
    _tipo->setMaximumWidth(500);
    _tipo->setVisible(false);

    //LISTA
    _TableList = new QTableWidget();
    _TableList->setMaximumWidth(500);
    _tempLayoutOpzioni->addWidget(_TableList);
    _TableList->setVisible(false);

    //BOTTONE 3 ( AGGIUNGI ROW )
    _aggiungiRiga = new QPushButton("Aggiungi Riga");
    _aggiungiRiga->setMaximumWidth(500);
    _tempLayoutOpzioni->addWidget(_aggiungiRiga);
    _aggiungiRiga->setVisible(false);

    //BOTTONE 1 ( AGGIUNGI )
    _aggiunta = new QPushButton("Aggiungi Nuova Annotazione");
    _aggiunta->setMaximumWidth(500);
    _tempLayoutOpzioni->addWidget(_aggiunta);

    //BOTTONE 2 ( AGGIORNA )
    _aggiorna = new QPushButton("Aggiorna");
    _aggiorna->setMaximumWidth(500);
    _tempLayoutOpzioni->addWidget(_aggiorna);



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
    _LineDesc->setVisible(false);
    _ora->setVisible(false);
    _calendario->setVisible(false);
    _tipo->setVisible(false);
    _TableList->setVisible(false);
    _aggiungiRiga->setVisible(false);
}

void view_annotazione::VisualizzaPromemoria()
{
    _LineCorpo->setVisible(true);
    _LineDesc->setVisible(false);
    _ora->setVisible(true);
    _calendario->setVisible(true);
    _tipo->setVisible(false);
    _TableList->setVisible(false);
    _aggiungiRiga->setVisible(false);
}

void view_annotazione::VisualizzaRicorrenza()
{
    _LineCorpo->setVisible(true);
    _LineDesc->setVisible(false);
    _ora->setVisible(true);
    _calendario->setVisible(true);
    _tipo->setVisible(true);
    _TableList->setVisible(false);
    _aggiungiRiga->setVisible(false);
}

void view_annotazione::VisualizzaElenco()
{
    _LineCorpo->setVisible(false);
    _LineDesc->setVisible(true);
    _ora->setVisible(false);
    _calendario->setVisible(false);
    _tipo->setVisible(false);
    _TableList->setVisible(true);
    _aggiungiRiga->setVisible(true);
    //SETUP TABLEVIEW
    _TableList->setColumnCount(1);
    _TableList->setRowCount(5);
    for(int i=0;i<5;i++)
    {
        _TableList->setItem(i,0,new QTableWidgetItem(""));
    }

    _TableList->setColumnWidth(0,_TableList->width()-20);
    _TableList->setShowGrid(true);
    _TableList->setHorizontalHeaderItem(0,new QTableWidgetItem("Elemento"));
}

void view_annotazione::VisualizzaSpesa()
{
    _LineCorpo->setVisible(false);
    _LineDesc->setVisible(true);
    _ora->setVisible(false);
    _calendario->setVisible(false);
    _tipo->setVisible(false);
    _TableList->setVisible(true);
    _aggiungiRiga->setVisible(true);

    //SETUP TABLEVIEW
    _TableList->setColumnCount(2);
    _TableList->setRowCount(5);
    _TableList->setColumnWidth(0,(_TableList->width()/2)-10);
    _TableList->setShowGrid(true);
    _TableList->setHorizontalHeaderItem(0,new QTableWidgetItem("Elemento"));
    _TableList->setColumnWidth(1,(_TableList->width()/2)-10);
    for(int i=0;i<5;i++)
    {
        _TableList->setItem(i,0,new QTableWidgetItem(""));
        _TableList->setItem(i,1,new QTableWidgetItem(""));
    }
    _TableList->setHorizontalHeaderItem(1,new QTableWidgetItem("Costo"));
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
        _nuovoInsert  = new ricorrenza(_LineTitolo->text(), _LineCorpo->document()->toRawText(),_calendario->selectedDate(),_ora->time(), MetodoSupporto(_tipo->currentIndex()));
    //Elenco
    else if (_value == 3)
    {
        lista<type_elenco*> *_ListaTableElenco = new lista<type_elenco*>();

        for(int i=0;i<_TableList->rowCount();i++)
        {
            if(! (_TableList->item(i,0)->text().isEmpty()) )
            {
                _ListaTableElenco->insertFront(new type_elenco(_TableList->item(i,0)->text()));
            }

        }

        _nuovoInsert = new elenco(_LineTitolo->text(),_LineDesc->document()->toRawText(),*_ListaTableElenco);
    }
    //Spesa
    else if (_value == 4)
    {
        lista<type_spesa*> *_ListaTableSpesa = new lista<type_spesa*>();
        double _ValueTemp = 0;
        for(int i=0;i<_TableList->rowCount();i++)
        {
            if(! (_TableList->item(i,0)->text().isEmpty()))
            {
                if(_TableList->item(i,1)->text().isEmpty())
                    _ListaTableSpesa->insertFront(new type_spesa( _TableList->item(i,0)->text(),0,0));
                else
                {
                    _ValueTemp = _TableList->item(i,1)->text().toDouble();
                    _ListaTableSpesa->insertFront(new type_spesa( _TableList->item(i,0)->text(),0,_ValueTemp));
                }
            }
        }

        _nuovoInsert = new spesa(_LineTitolo->text(),_LineDesc->document()->toRawText(),*_ListaTableSpesa);

    }

    wAnnotazione *_nuovoWAnn = new wAnnotazione(_nuovoInsert );
    _model->aggiungiAnnotazione(_nuovoInsert);
    _wA.insertFront(_nuovoWAnn);
    viewGriglia();
}

void view_annotazione::Aggiorna()
{
    viewGriglia();
}

void view_annotazione::OnClickRow()
{
    _TableList->insertRow(_TableList->rowCount());
    if(_TableList->columnCount()==1)
        _TableList->setItem(_TableList->rowCount()-1,0,new QTableWidgetItem(""));
    else
    {
        _TableList->setItem(_TableList->rowCount()-1,0,new QTableWidgetItem(""));
        _TableList->setItem(_TableList->rowCount()-1,1,new QTableWidgetItem(""));
    }
}


