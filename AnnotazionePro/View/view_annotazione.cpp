#include "view_annotazione.h"

// Costruttore
view_annotazione::view_annotazione(model_annotazione *model, QWidget *parent): QWidget(parent), _Model(model)
{
    _MainLayout = new QHBoxLayout(this);
    _Grid = new QVBoxLayout();
    _InsertAndOptions = new QVBoxLayout();
    // Setup Opzioni
    viewOpzioni();
    // Setup Griglia
    viewGriglia();
    _MainLayout->addLayout(_Grid,70);
    _MainLayout->addLayout(_InsertAndOptions,25);

    connect(_Tipologia, SIGNAL(currentIndexChanged(int)), this, SLOT(ComboBoxTypeChanged(int)));
    connect(_LineCorpo, SIGNAL(textChanged()), this, SLOT( OnTextChanged() ) );
    connect(_LineDesc, SIGNAL(textChanged()), this, SLOT( OnTextChanged() ) );
    //Bottone
    connect(_BtnAdd, SIGNAL( clicked() ), this, SLOT( OnClickBtnAggiungi() ));
    connect(_BtnAddRow, SIGNAL( clicked() ), this, SLOT( OnClickRow() ));
    connect(_BtnDeleteGrid, SIGNAL( clicked() ), this, SLOT( DeleteGrid() ));
    connect(_BtnLogClear, SIGNAL( clicked() ), this, SLOT( DeleteLog() ));


    // Signal Mapper per OnClick di wAnnotazione
    _SignalMapper = new QSignalMapper(this);
    connect(_SignalMapper, SIGNAL(mapped(int)), this, SLOT(OpenWindowDetails(int)));

}

// Distruttore
view_annotazione::~view_annotazione()
{
    delete _Model;
    _wA.clear();
    delete _MainLayout;
    delete _InsertAndOptions;
    delete _Grid;
    delete _LineTitolo;
    delete _LineCorpo;
    delete _LineDesc;
    delete _Tipologia;
    delete _Calendario;
    delete _Ora;
    delete _Ricorrenza;
    delete _TableList;
    delete _SignalMapper;
    delete _BtnAdd;
    delete _BtnAddRow;
    delete _BtnDeleteGrid;
    delete _LineLog;
}

void view_annotazione::ApriGriglia()
{
    QGridLayout *_tempLayoutGriglia = new QGridLayout();
    QGroupBox *_suppLayoutGriglia = new QGroupBox();

    _scrollAreaAnnot = new QScrollArea;
    _scrollAreaAnnot->setWidgetResizable(true);

    QRect geometry = _Grid->geometry();
    int width = geometry.width();
    _tempLayoutGriglia->setSpacing(width/25);

    clearGriglia();

    lista<annotazione*> temp=_Model->getAnnotazioni();
    wAnnotazione *_nuovoWAnn;
    _LineLog->append("[Apertura File] ");

    for(lista<annotazione*>::constiterator ci=temp.begin(); ci != temp.end();ci++)
    {
        _nuovoWAnn = new wAnnotazione(*ci);
        _wA.insertBack(_nuovoWAnn);
        SetSignalMapper(_nuovoWAnn);
        _LineLog->append("[Aggiunta elemento] \n"+(*ci)->ToString());
    }

    int count = 0;
    for(lista<wAnnotazione*>::constiterator cit = _wA.begin(); cit != _wA.end(); cit++)
    {
        resizeAnn(* cit);

        _tempLayoutGriglia->addWidget(*cit,  (count > 3) ? count/4 : 0, (count > 3) ? count-4*(count/4) : count);
        count++;
    }
    _tempLayoutGriglia->setAlignment(Qt::AlignTop);

    _suppLayoutGriglia->setLayout(_tempLayoutGriglia);
    _scrollAreaAnnot->setWidget(_suppLayoutGriglia);

    _Grid->addWidget(_scrollAreaAnnot);

}

// Creazione di Opzioni ( Parte a Destra )
void view_annotazione::viewOpzioni()
{

    QVBoxLayout *_tempLayoutOpzioni = new QVBoxLayout();
    QGroupBox *_GroupBoxInserimento = new QGroupBox("Inserimento");

    _LineTitolo = new QLineEdit();
    _LineCorpo = new QTextEdit();
    _LineDesc = new QTextEdit();
    _Tipologia = new QComboBox();
    _Calendario = new QCalendarWidget();
    _Ricorrenza = new QComboBox();

    _tempLayoutOpzioni->addWidget(new QLabel("Tipologia"));
    _Tipologia->addItems(model_annotazione::categorie());
    _tempLayoutOpzioni->addWidget(_Tipologia);

    // TITOLO
    _LineTitolo->setPlaceholderText("Titolo");
    _tempLayoutOpzioni->addWidget(_LineTitolo);

    // NOTA
    _LineCorpo->setPlaceholderText("Corpo");
    _LineCorpo->setMaximumHeight(23);
    _tempLayoutOpzioni->addWidget(_LineCorpo);

    //DESCRIZIONE
    _LineDesc->setPlaceholderText("Descrizione");
    _LineDesc->setMaximumHeight(23);
    _tempLayoutOpzioni->addWidget(_LineDesc);
    _LineDesc->setVisible(false);

    //ORA
    _Ora = new QDateTimeEdit(QDate::currentDate());
    _Ora->setDisplayFormat("hh:mm:ss");
    _tempLayoutOpzioni->addWidget(_Ora);
    _Ora->setVisible(false);
    _Ora->setTime(QTime::currentTime());

    //DATA

    _tempLayoutOpzioni->addWidget(_Calendario);
    _Calendario->setVisible(false);
    _Calendario->setSelectedDate(QDate::currentDate());
    _Calendario->setHorizontalHeaderFormat(QCalendarWidget::NoHorizontalHeader);
    _Calendario->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
   // _Calendario->setStyleSheet();

    //TIPO
    _Ricorrenza->addItems(metodi_extra::getTipi());
    _tempLayoutOpzioni->addWidget(_Ricorrenza);
    _Ricorrenza->setVisible(false);

    //LISTA
    _TableList = new QTableWidget();
    _tempLayoutOpzioni->addWidget(_TableList);
    _TableList->setVisible(false);

    //BOTTONE 3 ( AGGIUNGI ROW )
    _BtnAddRow = new QPushButton("Aggiungi Riga");
    _tempLayoutOpzioni->addWidget(_BtnAddRow);
    _BtnAddRow->setVisible(false);

    //BOTTONE 1 ( AGGIUNGI )
    _BtnAdd = new QPushButton("Aggiungi Nuova Annotazione");
    _tempLayoutOpzioni->addWidget(_BtnAdd);

    _GroupBoxInserimento->setLayout(_tempLayoutOpzioni);
    _GroupBoxInserimento->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);

    _InsertAndOptions->addWidget(_GroupBoxInserimento);


    QVBoxLayout *_tempLayoutLog = new QVBoxLayout();
    QGroupBox *_GroupBoxLog = new QGroupBox("Log");
    _LineLog = new QTextEdit();
    _LineLog->setReadOnly(true);

    _BtnLogClear = new QPushButton("Svuota Log");

    _tempLayoutLog->addWidget(_LineLog);
    _tempLayoutLog->addWidget(_BtnLogClear);

    _GroupBoxLog->setLayout(_tempLayoutLog);
    _InsertAndOptions->addWidget(_GroupBoxLog);

    // Bottone Clear
    QVBoxLayout *_tempLayoutDelete = new QVBoxLayout();
    QGroupBox *_GroupBoxDelete = new QGroupBox("Svuota Griglia");
    _BtnDeleteGrid = new QPushButton("Svuota");
    //_BtnDeleteGrid->setMinimumHeight(70);
    //_BtnDeleteGrid->setStyleSheet("font-size: 24px;");

    _tempLayoutDelete->addWidget(_BtnDeleteGrid);
    _GroupBoxDelete->setLayout(_tempLayoutDelete);
    _InsertAndOptions->addWidget(_GroupBoxDelete);
    _InsertAndOptions->setAlignment(_GroupBoxDelete,Qt::AlignBottom);
}

// Creazione della Griglia di wAnnotazioni
void view_annotazione::viewGriglia()
{
    QGridLayout *_tempLayoutGriglia = new QGridLayout();
    QGroupBox *_suppLayoutGriglia = new QGroupBox();

    _scrollAreaAnnot = new QScrollArea;
    _scrollAreaAnnot->setWidgetResizable(true);

    QRect geometry = _Grid->geometry();
    int width = geometry.width();
    _tempLayoutGriglia->setSpacing(width/25);

    clearGriglia();

    lista<annotazione*> temp=_Model->getAnnotazioni();
    wAnnotazione *_nuovoWAnn;

    for(lista<annotazione*>::constiterator ci=temp.begin(); ci != temp.end();ci++)
    {
        _nuovoWAnn = new wAnnotazione(*ci);
        _wA.insertBack(_nuovoWAnn);
        SetSignalMapper(_nuovoWAnn);
    }

    int count = 0;
    for(lista<wAnnotazione*>::constiterator cit = _wA.begin(); cit != _wA.end(); cit++)
    {
        resizeAnn(* cit);

        _tempLayoutGriglia->addWidget(*cit,  (count > 3) ? count/4 : 0, (count > 3) ? count-4*(count/4) : count);
        count++;
    }
    _tempLayoutGriglia->setAlignment(Qt::AlignTop);

    _suppLayoutGriglia->setLayout(_tempLayoutGriglia);
    _scrollAreaAnnot->setWidget(_suppLayoutGriglia);

    _Grid->addWidget(_scrollAreaAnnot);
}

void view_annotazione::viewGrigliaAlternativo(int i)
{
    QGridLayout *_tempLayoutGriglia = new QGridLayout();
    QGroupBox *_suppLayoutGriglia = new QGroupBox();

    _scrollAreaAnnot = new QScrollArea;
    _scrollAreaAnnot->setWidgetResizable(true);

    QRect geometry = _Grid->geometry();
    int width = geometry.width();
    _tempLayoutGriglia->setSpacing(width/25);

    clearGriglia();

    lista<annotazione*> temp=_Model->getAnnotazioni();
    wAnnotazione *_nuovoWAnn;
    for(lista<annotazione*>::constiterator ci=temp.begin(); ci != temp.end();ci++)
    {
        _nuovoWAnn = new wAnnotazione(*ci);
        _wA.insertBack(_nuovoWAnn);
        SetSignalMapper(_nuovoWAnn);
    }
    int count = 0;
    for(lista<wAnnotazione*>::constiterator cit = _wA.begin(); cit != _wA.end(); cit++)
    {
        resizeAnn(* cit);
        (*cit)->setEnabled(false);
        if(i==count)
        {
            (*cit)->setStyleSheet(" background-color: rgb(66, 245, 123)");
        }
        else
            (*cit)->setStyleSheet(" background-color: white");
        _tempLayoutGriglia->addWidget(*cit,  (count > 3) ? count/4 : 0, (count > 3) ? count-4*(count/4) : count);
        count++;
    }
    _tempLayoutGriglia->setAlignment(Qt::AlignTop);

    _suppLayoutGriglia->setLayout(_tempLayoutGriglia);
    _scrollAreaAnnot->setWidget(_suppLayoutGriglia);

    _Grid->addWidget(_scrollAreaAnnot);
}

void view_annotazione::SpostaSinistra(annotazione* a)
{
     _LineLog->append("[Spostamento a sinistra] \n"+a->ToString());
}

void view_annotazione::SpostaDestra(annotazione *a)
{
    _LineLog->append("[Spostamento a destra] \n" +a->ToString());
}

void view_annotazione::ModificaScrivi(annotazione *a)
{
    _LineLog->append("[Elemento modificato] \n"+a->ToString());
}

void view_annotazione::EliminaScrivi(annotazione *a)
{
    _LineLog->append("[Elemento eliminato] \n"+a->ToString());
}

// Quando creo un oggetto di tipo wAnnotazione, lo passiamo a questo metodo che aggiunge connette slot e signal
void view_annotazione::SetSignalMapper(wAnnotazione *_wAnn)
{
    _SignalMapper->setMapping(_wAnn,_wA.indexOfInt(_wAnn));
    connect(_wAnn, SIGNAL(clicked()), _SignalMapper, SLOT(map()));
}

// Ridimensionamento delle wAnnotazioni in base alla dimensione della finestra
void view_annotazione::resizeAnn(wAnnotazione* Ann)
{
    QRect geometry = _Grid->geometry();
    int width = geometry.width();
    int height = geometry.height();
    Ann->setMaximumSize(width/5,height/4);
    Ann->setFixedSize(width/5,height/4);
    Ann->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
}

// Evento Resize della Finestra
void view_annotazione::resizeEvent(QResizeEvent *event)
{
    for(lista<wAnnotazione*>::constiterator cit = _wA.begin(); cit != _wA.end(); cit++)
    {
        resizeAnn(*cit);
    }
    QWidget::resizeEvent(event);
}

void view_annotazione::clearGriglia()
{
    // Pulisce la Griglia dalle wAnnotazioni
    for (int i = 0; i < _Grid->count(); i++)
    {
       _Grid->itemAt(i)->widget()->deleteLater();
    }

    // Aggiornamento della Griglia
    for(lista<wAnnotazione*>::constiterator citt=_wA.begin(); citt != _wA.end();citt++)
    {
        _SignalMapper->removeMappings(*citt);
    }
    _wA.clear();
}

////// S L O T

// On Click aggiunge una nuova annotazione
void view_annotazione::OnClickBtnAggiungi()
{
    //if per tipologia
    int _value = _Tipologia->currentIndex();
    annotazione *_nuovoInsert =nullptr;
    //Nota
    if(_value==0)
        _nuovoInsert  = new nota(_LineTitolo->text(), _LineCorpo->document()->toRawText());
    //Promemoria
    else if (_value == 1)
        _nuovoInsert  = new promemoria(_LineTitolo->text(), _LineCorpo->document()->toRawText(),_Calendario->selectedDate(),_Ora->time());
    //Ricorrenza
    else if (_value == 2)
        _nuovoInsert  = new ricorrenza(_LineTitolo->text(), _LineCorpo->document()->toRawText(),_Calendario->selectedDate(),_Ora->time(), metodo_tipo::IntToTipo(_Ricorrenza->currentIndex()));
    //Elenco
    else if (_value == 3)
    {
        lista<type_elenco*> *_ListaTableElenco = new lista<type_elenco*>();

        for(int i=0;i<_TableList->rowCount();i++)
        {
            if(! (_TableList->item(i,0)->text().isEmpty()) )
            {
                _ListaTableElenco->insertBack(new type_elenco(_TableList->item(i,0)->text()));
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
                    _ListaTableSpesa->insertBack(new type_spesa( _TableList->item(i,0)->text(),0,0));
                else
                {
                    _ValueTemp = _TableList->item(i,1)->text().toDouble();
                    _ListaTableSpesa->insertBack(new type_spesa( _TableList->item(i,0)->text(),0,_ValueTemp));
                }
            }
        }
        _nuovoInsert = new spesa(_LineTitolo->text(),_LineDesc->document()->toRawText(),*_ListaTableSpesa);
    }

    wAnnotazione *_nuovoWAnn = new wAnnotazione(_nuovoInsert );
    if(_nuovoInsert != nullptr)
        _LineLog->append("[Aggiunta elemento] "+_nuovoInsert->ToString());
    _Model->aggiungiAnnotazione(_nuovoInsert);
    _wA.insertBack(_nuovoWAnn);
    SetSignalMapper(_nuovoWAnn);

    viewGriglia();
}

// Slot per refresh della Griglia
void view_annotazione::UpdateGrid()
{
    viewGriglia();
}

// On click Row, Aggiunge linee extra per inserimento nelle tabelle
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

// Index Change di Tipo di annotazione
void view_annotazione::ComboBoxTypeChanged(int index)
{
    if(index==0)
    {
        _LineCorpo->setVisible(true);
        _LineDesc->setVisible(false);
        _Ora->setVisible(false);
        _Calendario->setVisible(false);
        _Ricorrenza->setVisible(false);
        _TableList->setVisible(false);
        _BtnAddRow->setVisible(false);
    }

    else if (index == 1)
    {
        _LineCorpo->setVisible(true);
        _LineDesc->setVisible(false);
        _Ora->setVisible(true);
        _Calendario->setVisible(true);
        _Ricorrenza->setVisible(false);
        _TableList->setVisible(false);
        _BtnAddRow->setVisible(false);
    }

    else if (index == 2)
    {
        _LineCorpo->setVisible(true);
        _LineDesc->setVisible(false);
        _Ora->setVisible(true);
        _Calendario->setVisible(true);
        _Ricorrenza->setVisible(true);
        _TableList->setVisible(false);
        _BtnAddRow->setVisible(false);
    }

    else if (index == 3)
    {
        _LineCorpo->setVisible(false);
        _LineDesc->setVisible(true);
        _Ora->setVisible(false);
        _Calendario->setVisible(false);
        _Ricorrenza->setVisible(false);
        _TableList->setVisible(true);
        _BtnAddRow->setVisible(true);
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

    else if (index == 4){
        _LineCorpo->setVisible(false);
        _LineDesc->setVisible(true);
        _Ora->setVisible(false);
        _Calendario->setVisible(false);
        _Ricorrenza->setVisible(false);
        _TableList->setVisible(true);
        _BtnAddRow->setVisible(true);

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
        //_TableList->setItemDelegateForColumn(1,)
        _TableList->setHorizontalHeaderItem(1,new QTableWidgetItem("Costo"));

        }
}

// Slot per aggiungere spazio nel _LineCorpo o nel _LineDesc
void view_annotazione::OnTextChanged()
{
    if(_LineCorpo->isVisible())
    {
        QSize size = _LineCorpo->document()->size().toSize();
        _LineCorpo->setFixedHeight( size.height() + 3 );
    }
    else
    {
        QSize size = _LineDesc->document()->size().toSize();
        _LineDesc->setFixedHeight( size.height() + 3 );
    }
}

// Slot per svuotare la griglia
void view_annotazione::DeleteGrid()
{
    QMessageBox::StandardButton response= QMessageBox::question(this, "Svuotare la griglia?", "Vuoi svuotare la griglia?", QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
    if(response == QMessageBox::Yes)
    {
        _Model->reset();
        viewGriglia();
        _LineLog->append("[Griglia Svuotata] ");
    }
}

// Slot per abilitare la griglia dopo averla disabilitata con l'apertura di una finestra
void view_annotazione::GridEnable()
{
    for(lista<wAnnotazione*>::constiterator ci=_wA.begin();ci!=_wA.end();ci++)
   {
       (*ci)->setEnabled(true);
       (*ci)->setStyleSheet("background-color:White");
   }
    this->setEnabled(true);
}


// On Click di wAnnotazione, apre la finestra dettagli
void view_annotazione::OpenWindowDetails( int value)
{
    int i=0;
    view_finestra* _FinestraDescrizione = new view_finestra(_Model,_Model->getAnnotazione(value));

    for(lista<wAnnotazione*>::constiterator ci=_wA.begin();ci!=_wA.end();ci++)
    {       
        (*ci)->setEnabled(false);
        if(i==value)
            (*ci)->setStyleSheet("  background-color: rgb(66, 245, 123)");
        i++;
    }

    connect(_FinestraDescrizione ,SIGNAL(ClosedWindow()), this , SLOT(GridEnable()));
    connect(_FinestraDescrizione, SIGNAL(AggiornaGriglia()), this, SLOT(UpdateGrid()));
    connect(_FinestraDescrizione, SIGNAL(AggiornaGrigliaAlternativo(int)), this, SLOT(viewGrigliaAlternativo(int)));
    connect(_FinestraDescrizione, SIGNAL(SpostaSinLog(annotazione*)), this, SLOT(SpostaSinistra(annotazione*)));
    connect(_FinestraDescrizione, SIGNAL(SpostaDesLog(annotazione*)), this, SLOT(SpostaDestra(annotazione*)));
    connect(_FinestraDescrizione, SIGNAL(ModificaLog(annotazione*)), this, SLOT(ModificaScrivi(annotazione*)));
    connect(_FinestraDescrizione, SIGNAL(EliminaLog(annotazione*)), this, SLOT(EliminaScrivi(annotazione*)));
    _FinestraDescrizione->setMinimumWidth(500);
    _FinestraDescrizione->setMaximumHeight(700);
    _FinestraDescrizione->setWindowModality(Qt::ApplicationModal);
    _FinestraDescrizione->show();

}


void view_annotazione::DeleteLog()
{
    _LineLog->clear();
}



