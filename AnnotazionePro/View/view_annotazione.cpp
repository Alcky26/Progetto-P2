#include "view_annotazione.h"

// Costruttore
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
    _mainLayout->addLayout(_opzioni,25);

    connect(_tipologia, SIGNAL(currentIndexChanged(int)), this, SLOT(tipologiaIndexChanged(int)));
    connect(_LineCorpo, SIGNAL(textChanged()), this, SLOT( onTextChanged() ) );
    connect(_LineDesc, SIGNAL(textChanged()), this, SLOT( onTextChanged() ) );
    //Bottone
    connect(_aggiunta, SIGNAL(clicked()), this, SLOT(OnClick()));
    connect(_aggiungiRiga,SIGNAL(clicked()), this, SLOT(OnClickRow()));
    connect(_svuotaGriglia,SIGNAL(clicked()), this, SLOT(dumpGriglia()));


    // Signal Mapper per OnClick di wAnnotazione
    _SignalMapper = new QSignalMapper(this);
    connect(_SignalMapper, SIGNAL(mapped(int)), this, SLOT(ShowDettagli(int)));

}

// Distruttore
view_annotazione::~view_annotazione()
{
    delete _model;
    _wA.clear();
    delete _mainLayout;
    delete _opzioni;
    delete _griglia;
    delete _LineTitolo;
    delete _LineCorpo;
    delete _LineDesc;
    delete _tipologia;
    delete _calendario;
    delete _ora;
    delete _tipo;
    delete _TableList;
    delete _SignalMapper;
    delete _aggiunta;
    delete _aggiungiRiga;
    delete _svuotaGriglia;
}

// Creazione di Opzioni ( Parte a Destra )
void view_annotazione::viewOpzioni()
{

    QVBoxLayout *_tempLayoutOpzioni = new QVBoxLayout();
    QGroupBox *_GroupBoxInserimento = new QGroupBox("Inserimento");
    QGroupBox *_GroupBoxFiltro = new QGroupBox("Filtro");
    QGroupBox *_GroupBoxOrdinamento = new QGroupBox("Ordinamento");


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
    _ora->setTime(QTime::currentTime());

    //DATA
    _calendario->setMaximumWidth(500);
    _calendario->setGridVisible(true);
    _tempLayoutOpzioni->addWidget(_calendario);
    _calendario->setVisible(false);
    _calendario->setSelectedDate(QDate::currentDate());

    //TIPO
    _tipo->addItems(ricorrenza::getTipi());
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

    _GroupBoxInserimento->setLayout(_tempLayoutOpzioni);
    _GroupBoxInserimento->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);

    //Filtro
    QVBoxLayout *_VBoxFiltro = new QVBoxLayout;
    _checkAnn = new QCheckBox(" Filtra le Annotazioni ");
    _checkProm = new QCheckBox(" Filtra i Promemoria");
    _checkRic = new QCheckBox(" Filtra le Ricorrenze ");
    _checkEle = new QCheckBox(" Filtra gli Elenchi ");
    _checkSpes = new QCheckBox(" Filtra le Spese");

    _VBoxFiltro->addWidget(_checkAnn);
    _VBoxFiltro->addWidget(_checkProm);
    _VBoxFiltro->addWidget(_checkRic);
    _VBoxFiltro->addWidget(_checkEle);
    _VBoxFiltro->addWidget(_checkSpes);

    _GroupBoxFiltro->setLayout(_VBoxFiltro);

    //Ordinamento
    QVBoxLayout *_VBoxOrdinamento = new QVBoxLayout;
    QRadioButton *_RadioNormale = new QRadioButton("Normale");
    QRadioButton *_RadioInverso = new QRadioButton("Inverso");
    QRadioButton *_RadioData = new QRadioButton("Per Data (dal più recente)");
    QRadioButton *_RadioDataInverso = new QRadioButton("Per Data (dal meno recente)");
    QRadioButton *_RadioTipo = new QRadioButton("Per tipo");

    _VBoxOrdinamento->addWidget(_RadioNormale);
    _RadioNormale->setChecked(true);
    _VBoxOrdinamento->addWidget(_RadioInverso);
    _VBoxOrdinamento->addWidget(_RadioData);
    _VBoxOrdinamento->addWidget(_RadioDataInverso);
    _VBoxOrdinamento->addWidget(_RadioTipo);

    _GroupBoxOrdinamento->setLayout(_VBoxOrdinamento);

    // Bottone Clear
    _svuotaGriglia = new QPushButton("Svuota");
    _svuotaGriglia->setMaximumWidth(500);

    _opzioni->addWidget(_GroupBoxInserimento);
    _opzioni->addWidget(_GroupBoxFiltro);
    _opzioni->addWidget(_GroupBoxOrdinamento);
    _opzioni->addWidget(_svuotaGriglia);
    _opzioni->setAlignment(Qt::AlignTop);
    _opzioni->setAlignment(_svuotaGriglia,Qt::AlignBottom);
}

void view_annotazione::onTextChanged()
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

// Creazione della Griglia di wAnnotazioni
void view_annotazione::viewGriglia()
{
    QGridLayout *_tempLayoutGriglia = new QGridLayout();
    QGroupBox *_suppLayoutGriglia = new QGroupBox();

    QScrollArea *_scrollAreaAnnot = new QScrollArea;

    clearGriglia();

    QRect geometry = _griglia->geometry();
    int width = geometry.width();
    _tempLayoutGriglia->setSpacing(width/25);

    aggiornaGriglia(_tempLayoutGriglia);

    _suppLayoutGriglia->setLayout(_tempLayoutGriglia);
    _scrollAreaAnnot->setWidget(_suppLayoutGriglia);

    // TO FIX
    //_scrollAreaAnnot->setMinimumSize(200,200);
    //_scrollAreaAnnot->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::MinimumExpanding);
    _griglia->addWidget(_scrollAreaAnnot);

}

// Pulisce la Griglia dalle wAnnotazioni
void view_annotazione::clearGriglia()
{
    for (int i = 0; i < _griglia->count(); i++)
    {
       _griglia->itemAt(i)->widget()->deleteLater();
    }
}

void view_annotazione::dumpGriglia()
{
    QMessageBox::StandardButton response= QMessageBox::question(this, "Svuotare la griglia?", "Vuoi svuotare la griglia?", QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
    if(response == QMessageBox::Yes)
    {
        _model->reset();
        viewGriglia();
    }
}

// Ridimensionamento delle wAnnotazioni in base alla dimensione della finestra
void view_annotazione::resizeAnn(wAnnotazione* Ann)
{
    QRect geometry = _griglia->geometry();
    int width = geometry.width();
    int height = geometry.height();
    Ann->setMaximumSize(width/5,height/5);
    Ann->setFixedSize(width/5,height/5);
    Ann->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
}

// Aggiornamento valori di wAnnotazioni in caso di modifica degli elementi
void view_annotazione::aggiornaValoriGriglia()
{
    if(_wA.getSize()==_model->getAnnotazioni().getSize())/////////////////////////////PROBLEMONEEEEEEEEEEE
    {
        int i=0;
        for(lista<wAnnotazione*>::constiterator cit=_wA.begin(); cit != _wA.end();cit++)
        {
            (*cit)->aggiornaValori(_model->getAnnotazione(i));
            i++;
        }
    }
    else
    {
        for(lista<wAnnotazione*>::constiterator citt=_wA.begin(); citt != _wA.end();citt++)
        {
            _SignalMapper->removeMappings(*citt);
        }
        _wA.clear();
        lista<annotazione*> temp=_model->getAnnotazioni();
        wAnnotazione *_nuovoWAnn;
        for(lista<annotazione*>::constiterator ci=temp.begin(); ci != temp.end();ci++)
        {
            _nuovoWAnn = new wAnnotazione(*ci);
            _wA.insertBack(_nuovoWAnn);
            SetSignalMapper(_nuovoWAnn);
        }
    }
}

// Index Change di Tipo di annotazione
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

// As Title
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

// As Title
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

// As Title
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

// As Title
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

// As Title
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

// Aggiornamento della Griglia
void view_annotazione::aggiornaGriglia(QGridLayout *supplay)
{
    aggiornaValoriGriglia();
    int count = 0;
    for(lista<wAnnotazione*>::constiterator cit = _wA.begin(); cit != _wA.end(); cit++)
    {        
        resizeAnn(* cit);
        supplay->addWidget(*cit,  (count > 3) ? count/4 : 0, (count > 3) ? count-4*(count/4) : count);
        count++;
    }
    supplay->setAlignment(Qt::AlignTop);

}

// On Click aggiunge una nuova annotazione
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
        _nuovoInsert  = new ricorrenza(_LineTitolo->text(), _LineCorpo->document()->toRawText(),_calendario->selectedDate(),_ora->time(), metodi_extra::MetodoSupporto(_tipo->currentIndex()));
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
    _wA.insertBack(_nuovoWAnn);
    SetSignalMapper(_nuovoWAnn);
    viewGriglia();
}

// Slot per Button Aggiorna, Refresha i valori della Griglia
void view_annotazione::Aggiorna()
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

// On Click di wAnnotazione, apre la finestra dettagli
void view_annotazione::ShowDettagli( int value)
{
    view_finestra* _FinestraDescrizione = new view_finestra(_model,_model->getAnnotazione(value));
    for(lista<wAnnotazione*>::constiterator ci=_wA.begin();ci!=_wA.end();ci++)
    {
        (*ci)->setEnabled(false);
    }
    connect(_FinestraDescrizione ,SIGNAL(ClosedWindow()), this , SLOT(SetGrigliaEnabled()));
    connect(_FinestraDescrizione, SIGNAL(Modificato()), this, SLOT(Aggiorna()));
    connect(_FinestraDescrizione, SIGNAL(Eliminato()), this, SLOT(Aggiorna()));
    _FinestraDescrizione->show();
}

// Quando creo un oggetto di tipo wAnnotazione, lo passiamo a questo metodo che aggiunge connette slot e signal
void view_annotazione::SetSignalMapper(wAnnotazione *_wAnn)
{
    _SignalMapper->setMapping(_wAnn,_wA.indexOfInt(_wAnn));
    connect(_wAnn, SIGNAL(clicked()), _SignalMapper, SLOT(map()));
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

void view_annotazione::AggiornaConFiltro()
{
    clearGriglia();

    for(lista<wAnnotazione*>::constiterator cit = _wA.begin(); cit != _wA.end(); cit++)
    {

    }

}

void view_annotazione::AggiornaConOrdinamento()
{

}

// Abilità la griglia dopo una chiusura di finestra aggiuntiva
void view_annotazione::SetGrigliaEnabled()
{
    for(lista<wAnnotazione*>::constiterator ci=_wA.begin();ci!=_wA.end();ci++)
    {
        (*ci)->setEnabled(true);
    }
}

