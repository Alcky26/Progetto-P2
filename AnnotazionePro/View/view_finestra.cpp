#include "view_finestra.h"

// Costruttore
view_finestra::view_finestra(model_annotazione *model, annotazione *ann, QWidget *parent) : QWidget(parent),  _model(model)
{
    _mainLayout = new QVBoxLayout(this);

    _ann = ann;

    _StatoModifica = false;

    setupTitolo();

    // Se è di tipo Promemoria, aggiungiamo Data e Ora
    if(dynamic_cast<promemoria*>(ann))
    {
        //Ora
        _ora = new QDateTimeEdit(dynamic_cast<promemoria*>(ann)->getTime());
        //Calendario
        _calendario = new QCalendarWidget();
        _calendario->setSelectedDate(dynamic_cast<promemoria*>(ann)->getDate());
        setupDataOra();
    }

    // Se è di tipo Ricorrenza, aggiungiamo Data, Ora e Tipo
    if(dynamic_cast<ricorrenza*>(ann))
    {
        // Ora
        _ora = new QDateTimeEdit(dynamic_cast<ricorrenza*>(ann)->getTime());
        // Calendario
        _calendario = new QCalendarWidget();
        _calendario->setSelectedDate(dynamic_cast<ricorrenza*>(ann)->getDate());
        setupDataOra();
        // Tipo
        _tipo=new QComboBox();
        _tipo->addItems(ricorrenza::getTipi());
        _mainLayout->addWidget(_tipo);
        _tipo->setEnabled(false);

    }

    // Se è di tipo Nota, Ricorrenza o Promemoria
    if(dynamic_cast<nota*>(ann))
    {
        // Corpo
        _BoxCorpo = new QGroupBox("Corpo");
        QVBoxLayout *_CorpoLayout = new QVBoxLayout();
        _LineCorpo = new QTextEdit(dynamic_cast<nota*>(ann)->getCorpo());
        _LineCorpo->setEnabled(false);
        _CorpoLayout->addWidget(_LineCorpo);
        _BoxCorpo->setLayout(_CorpoLayout);
        _mainLayout->addWidget(_BoxCorpo);
    }

    // Se è di tipo Elenco ( Escludiamo Spesa che è figlia )
    if(dynamic_cast<elenco*>(ann) && !dynamic_cast<spesa*>(ann))
    {
        _LineDesc = new QTextEdit(dynamic_cast<elenco*>(ann)->getDescrizione());
        setupDescrizione();

        _BoxTable = new QGroupBox(" Lista Elementi ");
        QVBoxLayout *_TableLayout = new QVBoxLayout();

        // Tabella
        _TableList = new QTableWidget();
        _TableList->setShowGrid(true);
        _TableList->setColumnCount(2);
        //_TableList->setColumnWidth(0,250);
        _TableList->setHorizontalHeaderItem(0,new QTableWidgetItem("Elemento"));
        _TableList->setHorizontalHeaderItem(1,new QTableWidgetItem("Conferma"));
        // Riempimento Tabella
        int i=0;
        lista<type_elenco*> _SupportList =  dynamic_cast<elenco*>(ann)->getElenco();
        _TableList->setRowCount(_SupportList.getSize());
        _TableList->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for(lista<type_elenco*>::constiterator ci = _SupportList.begin() ; ci!=_SupportList.end() ; ci++)
        {

            _TableList->setItem(i,0,new QTableWidgetItem(_SupportList.index(ci)->getValue()));
            QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
            checkBoxItem->setCheckState(Qt::Unchecked);
            checkBoxItem->setText("effettuato");
            _TableList->setItem(i,1,checkBoxItem);
            i++;
        }
        //  _TableList->setEnabled(false);
        _TableLayout->addWidget(_TableList);
        _BoxTable->setLayout(_TableLayout);
        _mainLayout->addWidget(_BoxTable);
    }

    // Se è di tipo Spesa
    if(dynamic_cast<spesa*>(ann))
    {
        // Descrizione
        _LineDesc = new QTextEdit(dynamic_cast<spesa*>(ann)->getDescrizione());
        setupDescrizione();

        _BoxTable = new QGroupBox(" Lista Elementi ");
        QVBoxLayout *_TableLayout = new QVBoxLayout();

        // Tabella
        _TableList = new QTableWidget();
        _TableList->setShowGrid(true);
        _TableList->setColumnCount(3);
        //_TableList->setColumnWidth(0,125);
        //_TableList->setColumnWidth(0,125);
        _TableList->setHorizontalHeaderItem(0,new QTableWidgetItem("Elemento"));
        _TableList->setHorizontalHeaderItem(1,new QTableWidgetItem("Costo"));
        _TableList->setHorizontalHeaderItem(2,new QTableWidgetItem("Conferma"));

        // Riempimento Tabella
        int i=0;
        lista<type_spesa*> _SupportList =  dynamic_cast<spesa*>(ann)->getSpesa();
        _TableList->setRowCount(_SupportList.getSize());
        _TableList->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for(lista<type_spesa*>::constiterator ci = _SupportList.begin() ; ci!=_SupportList.end() ; ci++)
        {
            _TableList->setItem(i,0,new QTableWidgetItem(_SupportList.index(ci)->getValue()));
            _TableList->setItem(i,1,new QTableWidgetItem(QString::number(_SupportList.index(ci)->getCost())));
            QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
            checkBoxItem->setCheckState(Qt::Unchecked);
            _TableList->setItem(i,2,checkBoxItem);
            i++;
        }
        //_TableList->setEnabled(false);
        _TableLayout->addWidget(_TableList);
        _BoxTable->setLayout(_TableLayout);
        _mainLayout->addWidget(_BoxTable);
    }

    _elimina = new QPushButton("Elimina Questo Elemento");
    _modifica = new QPushButton("Modifica Valori di Questo Elemento");

    _mainLayout->addWidget(_modifica);
    _mainLayout->addWidget(_elimina);

    connect(_elimina,SIGNAL(clicked()),this,SLOT(OnClickElimina()));
    connect(_modifica,SIGNAL(clicked()),this,SLOT(OnClickModifica()));

}

// Distruttore
view_finestra::~view_finestra()
{
    delete _model;
    delete _ann;
    delete _mainLayout;
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
void view_finestra::SetAllEnabled(bool _boolean)
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
        _LineDesc->setReadOnly(_boolean);
        if(_boolean)
            _TableList->setEditTriggers(QAbstractItemView::AllEditTriggers);
        else
            _TableList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        //_TableList->setEnabled(_boolean);
    }
    if(dynamic_cast<spesa*>(_ann))
    {
        _LineDesc->setReadOnly(_boolean);
        if(_boolean)
            _TableList->setEditTriggers(QAbstractItemView::AllEditTriggers);
        else
            _TableList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        //_TableList->setEnabled(_boolean);
    }
}

// Legge i valori modificati per modificare i valori al Model
annotazione* view_finestra::ReadChangedValues()
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
        return new ricorrenza(_LineTitolo->text(),_LineCorpo->document()->toRawText(),_calendario->selectedDate(),_ora->time(),dynamic_cast<ricorrenza*>(_ann)->QStringToTipo(_tipo->itemData(_tipo->currentIndex()).toString()));
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
    //if (tabellaModel->deviSalvare())
    //{
    //    checkUnsavedData();
    //}
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
    _mainLayout->addWidget(_BoxTitolo);
    //_mainLayout->addWidget(_LineTitolo);
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
    _mainLayout->addWidget(_BoxDataOra);
}

void view_finestra::setupDescrizione()
{
    // Descrizione
    _BoxDesc = new QGroupBox("Descrizione");
    QVBoxLayout *_DescrizioneLayout = new QVBoxLayout();
    _LineDesc->setEnabled(false);
    _DescrizioneLayout->addWidget(_LineDesc);
    _BoxDesc->setLayout(_DescrizioneLayout);
    _mainLayout->addWidget(_BoxDesc);
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
        _model->modificaElemento(_model->getAnnotazioni().indexOfInt(_ann),ReadChangedValues());
        emit Modificato();
    }
}

// Slot per il bottone di Elimina
void view_finestra::OnClickElimina()
{
    QMessageBox::StandardButton response= QMessageBox::question(this, "Elimina?",
                                                                "Sei sicuro di voler elimina questa annotazione?", QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
    if(response == QMessageBox::Yes)
    {
        _model->rimouviElemento(_ann);
        emit Eliminato();
        this->close();
    }
}


