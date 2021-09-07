#include "view_finestra.h"

// Costruttore
view_finestra::view_finestra(model_annotazione *model, annotazione *ann, QWidget *parent) : QWidget(parent),  _Model(model)
{
    _MainLayout = new QVBoxLayout(this);

    _ann = ann;

    _StatoModifica = false;

    setupTitolo();

    // Se è di tipo Promemoria, aggiungiamo Data e Ora
    if(dynamic_cast<promemoria*>(ann))
    {
        promemoria* _prom = dynamic_cast<promemoria*>(ann);
        //Ora
        _ora = new QDateTimeEdit(_prom->getTime());
        //Calendario
        _calendario = new QCalendarWidget();
        _calendario->setSelectedDate(_prom->getDate());
        setupDataOra();
    }



    // Se è di tipo Ricorrenza, aggiungiamo Data, Ora e Tipo
    if(dynamic_cast<ricorrenza*>(ann))
    {
        ricorrenza* _rico= dynamic_cast<ricorrenza*>(ann);
        // Ora
        _ora = new QDateTimeEdit(_rico->getTime());
        // Calendario
        _calendario = new QCalendarWidget();
        _calendario->setSelectedDate(_rico->getDate());
        setupDataOra();
        // Tipo
        _tipo=new QComboBox();
        _tipo->addItems(metodi_extra::getTipi());
        _MainLayout->addWidget(_tipo);
        _tipo->setCurrentIndex(_rico->getType());
        _tipo->setEnabled(false);

    }

    // Se è di tipo Nota, Ricorrenza o Promemoria
    if(dynamic_cast<nota*>(ann))
    {
        nota* _nota= dynamic_cast<nota*>(ann);
        // Corpo
        _BoxCorpo = new QGroupBox("Corpo");
        QVBoxLayout *_CorpoLayout = new QVBoxLayout();
        _LineCorpo = new QTextEdit(_nota->getCorpo());
        _LineCorpo->setEnabled(false);
        _CorpoLayout->addWidget(_LineCorpo);
        _BoxCorpo->setLayout(_CorpoLayout);
        _MainLayout->addWidget(_BoxCorpo);
    }

    // Se è di tipo Elenco ( Escludiamo Spesa che è figlia )
    if(dynamic_cast<elenco*>(ann) && !dynamic_cast<spesa*>(ann))
    {
        elenco* _ele = dynamic_cast<elenco*>(ann);

        _LineDesc = new QTextEdit(_ele->getDescrizione());
        setupDescrizione();

        _BoxTable = new QGroupBox(" Lista Elementi ");
        QVBoxLayout *_TableLayout = new QVBoxLayout();

        // Tabella
        _TableList = new QTableWidget();
        _TableList->setShowGrid(true);
        _TableList->setColumnCount(2);
        _TableList->setHorizontalHeaderItem(0,new QTableWidgetItem("Elemento"));
        _TableList->setColumnWidth(0,300);
        _TableList->setHorizontalHeaderItem(1,new QTableWidgetItem(""));
        _TableList->setColumnWidth(1,25);
        // Riempimento Tabella
        int i=0;
        lista<type_elenco*> _SupportList = _ele->getElenco();
        _TableList->setRowCount(_SupportList.getSize());
        _TableList->setEnabled(false);

        for(lista<type_elenco*>::constiterator ci = _SupportList.begin() ; ci!=_SupportList.end() ; ci++)
        {

            _TableList->setItem(i,0,new QTableWidgetItem(_SupportList.index(ci)->getValue()));
            QTableWidgetItem *checkBoxItem = new QTableWidgetItem();

            if( (*ci)->getIsDone() )
                 checkBoxItem->setCheckState(Qt::Checked);
            else
                 checkBoxItem->setCheckState(Qt::Unchecked);

            _TableList->setItem(i,1,checkBoxItem);
            i++;
        }
        //  _TableList->setEnabled(false);
        _TableLayout->addWidget(_TableList);
        _BtnAddRow = new QPushButton("Aggiungi una Nuova Riga");
        _BtnAddRow->setEnabled(false);
        _TableLayout->addWidget(_BtnAddRow);
        _BoxTable->setLayout(_TableLayout);
        _MainLayout->addWidget(_BoxTable);
        connect(_BtnAddRow, SIGNAL( clicked() ), this, SLOT( AggiungiRiga() ));
    }

    // Se è di tipo Spesa
    if(dynamic_cast<spesa*>(ann))
    {
        spesa* _spe = dynamic_cast<spesa*>(ann);

        // Descrizione
        _LineDesc = new QTextEdit(_spe->getDescrizione());
        setupDescrizione();

        _BoxTable = new QGroupBox(" Lista Elementi ");
        QVBoxLayout *_TableLayout = new QVBoxLayout();

        // Tabella
        _TableList = new QTableWidget();
        _TableList->setShowGrid(true);
        _TableList->setColumnCount(3);
        _TableList->setHorizontalHeaderItem(0,new QTableWidgetItem("Elemento"));
        _TableList->setColumnWidth(0,120);
        _TableList->setHorizontalHeaderItem(1,new QTableWidgetItem("Costo"));
        _TableList->setColumnWidth(1,120);
        _TableList->setHorizontalHeaderItem(2,new QTableWidgetItem(""));
        _TableList->setColumnWidth(2,25);
        _TableList->resizeColumnToContents(2);

        // Riempimento Tabella
        int i=0;
        lista<type_spesa*> _SupportList =  _spe->getSpesa();
        _TableList->setRowCount(_SupportList.getSize());
        _TableList->setEnabled(false);

        //_TableList->setEnabled(false);
        for(lista<type_spesa*>::constiterator ci = _SupportList.begin() ; ci!=_SupportList.end() ; ci++)
        {
            _TableList->setItem(i,0,new QTableWidgetItem(_SupportList.index(ci)->getValue()));
            _TableList->setItem(i,1,new QTableWidgetItem(QString::number(_SupportList.index(ci)->getCost())));
            QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
            if( (*ci)->getIsDone() )
                 checkBoxItem->setCheckState(Qt::Checked);
            else
                 checkBoxItem->setCheckState(Qt::Unchecked);
            _TableList->setItem(i,2,checkBoxItem);
            i++;
        }
        //_TableList->setEnabled(false);

        _TableLayout->addWidget(_TableList);


        _BtnAddRow = new QPushButton("Aggiungi una Nuova Riga");
        _BtnAddRow->setEnabled(false);
        _TableLayout->addWidget(_BtnAddRow);

        _BoxTable->setLayout(_TableLayout);
        _MainLayout->addWidget(_BoxTable);
        connect(_BtnAddRow, SIGNAL( clicked() ), this, SLOT( AggiungiRiga() ));
    }

    _elimina = new QPushButton("Elimina Questo Elemento");
    _modifica = new QPushButton("Modifica Valori di Questo Elemento");
    _BtnLeft = new QPushButton("⟸ Sposta a Sinistra");
    _BtnRight = new QPushButton("Sposta a Destra ⟹");

    if(_ann==model->getAnnotazioni().front())
        _BtnLeft->setEnabled(false);
    if(_ann==model->getAnnotazioni().back())
        _BtnRight->setEnabled(false);

    QGridLayout *_LayoutLeftRight = new QGridLayout();
    _LayoutLeftRight->addWidget(_BtnLeft,1,0,Qt::AlignTop);
    _LayoutLeftRight->addWidget(_BtnRight,1,1,Qt::AlignTop);
    _MainLayout->addLayout(_LayoutLeftRight);

    _MainLayout->addWidget(_modifica);
    _MainLayout->addWidget(_elimina);

    connect(_elimina,SIGNAL(clicked()),this,SLOT(OnClickElimina()));
    connect(_modifica,SIGNAL(clicked()),this,SLOT(OnClickModifica()));
    connect(_BtnLeft, SIGNAL( clicked() ), this, SLOT( MoveWAnnLeft() ));
    connect(_BtnRight, SIGNAL( clicked() ), this, SLOT( MoveWAnnRight() ));
}

// Distruttore
view_finestra::~view_finestra()
{
    delete _Model;
    delete _ann;
    delete _MainLayout;
    delete _LineTitolo;
    delete _LineCorpo;
    delete _LineDesc;
    delete _calendario;
    delete _ora;
    delete _TableList;
    delete _tipo;
    delete _elimina;
    delete _modifica;
}

// Setta tutti i widget a interagibile o non interagibile
void view_finestra::SetAllEnabled(const bool _boolean)
{
    _LineTitolo->setEnabled(_boolean);
    if(dynamic_cast<ricorrenza*>(_ann))
    {
        _ora->setEnabled(_boolean);
        _calendario->setEnabled(_boolean);
        _tipo->setEnabled(_boolean);
    }

    if(dynamic_cast<promemoria*>(_ann))
    {
        _ora->setEnabled(_boolean);
        _calendario->setEnabled(_boolean);
    }

    if(dynamic_cast<nota*>(_ann))
    {
        _LineCorpo->setEnabled(_boolean);
    }

    if(dynamic_cast<elenco*>(_ann))
    {
        _LineDesc->setEnabled(_boolean);
        _TableList->setEnabled(_boolean);
        _BtnAddRow->setEnabled(_boolean);
    }

    if(dynamic_cast<spesa*>(_ann))
    {
        _LineDesc->setEnabled(_boolean);
        _TableList->setEnabled(_boolean);
        _BtnAddRow->setEnabled(_boolean);
    }
}

// Legge i valori modificati per modificare i valori al Model
annotazione* view_finestra::ReadChangedValues() const
{
    if(dynamic_cast<spesa*>(_ann) )
    {
        lista<type_spesa*> *_ListaTableSpesa = new lista<type_spesa*>();
        double _ValueTemp = 0;
        for(int i=0;i<_TableList->rowCount();i++)
        {
            _ValueTemp = _TableList->item(i,1)->text().toDouble();
            _ListaTableSpesa->insertBack(new type_spesa( _TableList->item(i,0)->text(),_TableList->item(i,2)->checkState(),_ValueTemp));

        }
        return new spesa(_LineTitolo->text(),_LineDesc->document()->toRawText(),*_ListaTableSpesa);
    }

    else if (dynamic_cast<elenco*>(_ann) )
    {
        lista<type_elenco*> *_ListaTableElenco = new lista<type_elenco*>();
        for(int i=0;i<_TableList->rowCount();i++)
        {
            _ListaTableElenco->insertBack(new type_elenco( _TableList->item(i,0)->text(),_TableList->item(i,1)->checkState() ));

        }
        return new elenco(_LineTitolo->text(),_LineDesc->document()->toRawText(),*_ListaTableElenco);
    }

    else if (dynamic_cast<promemoria*>(_ann))
    {
        return new promemoria(_LineTitolo->text(),_LineCorpo->document()->toRawText(),_calendario->selectedDate(),_ora->time());
    }

    else if (dynamic_cast<ricorrenza*>(_ann))
    {
        return new ricorrenza(_LineTitolo->text(),_LineCorpo->document()->toRawText(),_calendario->selectedDate(),_ora->time(),metodo_tipo::IntToTipo(_tipo->currentIndex()) );
    }

    else if (dynamic_cast<nota*>(_ann))
    {
       return new nota(_LineTitolo->text(),_LineCorpo->document()->toRawText());
    }

    return nullptr;
}

// Evento chiusura di una finestra
void view_finestra::closeEvent(QCloseEvent *event)
{
    emit ClosedWindow();
    event->accept();
}

void view_finestra::setupTitolo()
{
    // Titolo
    _BoxTitolo = new QGroupBox(" Titolo ");
    QVBoxLayout *_TitoloLayout = new QVBoxLayout();
    _LineTitolo= new QLineEdit();
    _LineTitolo->setText(_ann->getTitolo());
    _LineTitolo->setEnabled(false);
    _TitoloLayout->addWidget(_LineTitolo);
    _BoxTitolo->setLayout(_TitoloLayout);
    _MainLayout->addWidget(_BoxTitolo);
}

void view_finestra::setupDataOra()
{
    _BoxDataOra = new QGroupBox("Data & Ora");
    QVBoxLayout *_DataOraLayout = new QVBoxLayout();
    _ora->setEnabled(false);
    _DataOraLayout->addWidget(_ora);
    _calendario->setEnabled(false);
    _DataOraLayout->addWidget(_calendario);
    _BoxDataOra->setLayout(_DataOraLayout);
    _MainLayout->addWidget(_BoxDataOra);
}

void view_finestra::setupDescrizione()
{
    // Descrizione
    _BoxDesc = new QGroupBox("Descrizione");
    QVBoxLayout *_DescrizioneLayout = new QVBoxLayout();
    _LineDesc->setEnabled(false);
    _DescrizioneLayout->addWidget(_LineDesc);
    _BoxDesc->setLayout(_DescrizioneLayout);
    _MainLayout->addWidget(_BoxDesc);
}

// Slot per il bottone di Modifica
void view_finestra::OnClickModifica()
{
    if(!_StatoModifica)
    {
        _StatoModifica=true;
        _modifica->setText("Conferma Modifica");
        SetAllEnabled(_StatoModifica);
    }
    else
    {
        _StatoModifica=false; 
        _modifica->setText("Modifica Valori di Questo Elemento");
        SetAllEnabled(_StatoModifica);
        bool result = _Model->modificaElemento(_Model->getAnnotazioni().indexOfInt(_ann),ReadChangedValues());
        if(result) {
            emit AggiornaGrigliawValue(_Model->getAnnotazioni().indexOfInt(_ann));
            emit ModificaLog(_ann) ;
        }
        else
            emit StringLog("[Nessun Elemento Modificato]");
    }
}

// Slot per il bottone di Elimina
void view_finestra::OnClickElimina()
{
    QMessageBox::StandardButton response= QMessageBox::question(this, "Elimina?",
                                                                "Sei sicuro di voler elimina questa annotazione?", QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
    if(response == QMessageBox::Yes)
    {
        _Model->rimouviElemento(_ann);
        emit AggiornaGriglia();
        emit EliminaLog(_ann);
        this->close();
    }
}

void view_finestra::MoveWAnnLeft()
{
    lista<annotazione*> temp=_Model->getAnnotazioni();
    for(lista<annotazione*>::constiterator ci=temp.begin();ci!=temp.end();ci++)
    {
        if((*ci)==_ann)
        {
            _BtnRight->setEnabled(true);
            if(_Model->muoviElementoSx(ci))
            {
                if(!_Model->muoviElementoSx(ci))
                {
                    _BtnLeft->setEnabled(false);
                }
                else
                {
                    _Model->muoviElementoDx(ci);
                }
                emit AggiornaGrigliawValue(_Model->getAnnotazioni().indexOfInt(_ann));
                emit SpostaSinLog(_ann);
            }
        }
    }
}

void view_finestra::MoveWAnnRight()
{
    lista<annotazione*> temp=_Model->getAnnotazioni();
    for(lista<annotazione*>::constiterator ci=temp.begin();ci!=temp.end();ci++)
    {
        if((*ci)==_ann)
        {
            _BtnLeft->setEnabled(true);
            if(_Model->muoviElementoDx(ci))
            {
                if(!_Model->muoviElementoDx(ci))
                {
                    _BtnRight->setEnabled(false);
                }
                else
                {
                    _Model->muoviElementoSx(ci);
                }
                emit AggiornaGrigliawValue(_Model->getAnnotazioni().indexOfInt(_ann));
                emit SpostaDesLog(_ann);
            }
        }
    }
}

void view_finestra::AggiungiRiga()
{

    _TableList->insertRow(_TableList->rowCount());
    if(_TableList->columnCount()==2)
    {
        _TableList->setItem(_TableList->rowCount()-1,0,new QTableWidgetItem(""));
        QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setCheckState(Qt::Unchecked);
        _TableList->setItem(_TableList->rowCount()-1,1,checkBoxItem);
        emit StringLog("[Aggiunta riga di Elenco]");
    }
    else
    {
        _TableList->setItem(_TableList->rowCount()-1,0,new QTableWidgetItem(""));
        _TableList->setItem(_TableList->rowCount()-1,1,new QTableWidgetItem(""));
        QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setCheckState(Qt::Unchecked);
        _TableList->setItem(_TableList->rowCount()-1,2,checkBoxItem);
        emit StringLog("[Aggiunta riga di Spesa]");
    }

}

