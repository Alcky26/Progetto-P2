#include "view_finestra.h"

/*view_finestra::view_finestra():_model()
{

}*/

view_finestra::view_finestra(model_annotazione *model, annotazione *ann, QWidget *parent) : QWidget(parent),  _model(model)
{
    _mainLayout = new QVBoxLayout(this);

    _ann = ann;

    _StatoModifica = false;

    // Titolo
    _LineTitolo= new QLineEdit();
    _LineTitolo->setText(ann->getTitolo());
    _LineTitolo->setEnabled(false);
    _mainLayout->addWidget(_LineTitolo);

    // Se è di tipo Promemoria, aggiungiamo Data e Ora
    if(dynamic_cast<promemoria*>(ann))
    {
        // Ora
        _ora = new QDateTimeEdit(dynamic_cast<promemoria*>(ann)->getTime());
        _ora->setEnabled(false);
        _mainLayout->addWidget(_ora);
        // Calendario
        _calendario = new QCalendarWidget();
        _calendario->setSelectedDate(dynamic_cast<promemoria*>(ann)->getDate());
        _calendario->setEnabled(false);
        _mainLayout->addWidget(_calendario);
    }

    // Se è di tipo Ricorrenza, aggiungiamo Data, Ora e Tipo
    if(dynamic_cast<ricorrenza*>(ann))
    {
        // Ora
        _ora = new QDateTimeEdit(dynamic_cast<ricorrenza*>(ann)->getTime());
        _ora->setEnabled(false);
        _mainLayout->addWidget(_ora);
        // Calendario
        _calendario = new QCalendarWidget();
        _calendario->setSelectedDate(dynamic_cast<ricorrenza*>(ann)->getDate());
        _calendario->setEnabled(false);
        _mainLayout->addWidget(_calendario);
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
        _LineCorpo = new QTextEdit(dynamic_cast<nota*>(ann)->getCorpo());
        _LineCorpo->setEnabled(false);
        _mainLayout->addWidget(_LineCorpo);
    }

    // Se è di tipo Elenco ( Escludiamo Spesa che è figlia )
    if(dynamic_cast<elenco*>(ann) && !dynamic_cast<spesa*>(ann))
    {
        // Descrizione
        _LineDesc = new QTextEdit(dynamic_cast<elenco*>(ann)->getDescrizione());
        _LineDesc->setEnabled(false);
        _mainLayout->addWidget(_LineDesc);

        // Tabella
        _TableList = new QTableWidget();
        _TableList->setShowGrid(true);
        _TableList->setColumnCount(1);
        _TableList->setColumnWidth(0,250);
        _TableList->setHorizontalHeaderItem(0,new QTableWidgetItem("Elemento"));

        // Riempimento Tabella
        int i=0;
        lista<type_elenco*> _SupportList =  dynamic_cast<elenco*>(ann)->getElenco();
        _TableList->setRowCount(_SupportList.getSize());

        for(lista<type_elenco*>::constiterator ci = _SupportList.begin() ; ci!=_SupportList.end() ; ci++)
        {

            _TableList->setItem(i,0,new QTableWidgetItem(_SupportList.index(ci)->getValue()));
            i++;
        }
        _TableList->setEnabled(false);
        _mainLayout->addWidget(_TableList);
    }

    // Se è di tipo Spesa
    if(dynamic_cast<spesa*>(ann))
    {
        // Descrizione
        _LineDesc = new QTextEdit(dynamic_cast<spesa*>(ann)->getDescrizione());
        _LineDesc->setEnabled(false);
        _mainLayout->addWidget(_LineDesc);

        // Tabella
        _TableList = new QTableWidget();
        _TableList->setShowGrid(true);
        _TableList->setColumnCount(2);
        _TableList->setColumnWidth(0,125);
        _TableList->setColumnWidth(0,125);
        _TableList->setHorizontalHeaderItem(0,new QTableWidgetItem("Elemento"));
        _TableList->setHorizontalHeaderItem(1,new QTableWidgetItem("Costo"));

        // Riempimento Tabella
        int i=0;
        lista<type_spesa*> _SupportList =  dynamic_cast<spesa*>(ann)->getSpesa();
        _TableList->setRowCount(_SupportList.getSize());

        for(lista<type_spesa*>::constiterator ci = _SupportList.begin() ; ci!=_SupportList.end() ; ci++)
        {
            _TableList->setItem(i,0,new QTableWidgetItem(_SupportList.index(ci)->getValue()));
            _TableList->setItem(i,1,new QTableWidgetItem(QString::number(_SupportList.index(ci)->getCost())));
            i++;
        }
        _TableList->setEnabled(false);
        _mainLayout->addWidget(_TableList);
    }

    _elimina = new QPushButton("Elimina Questo Elemento");
    _modifica = new QPushButton("Modifica Valori di Questo Elemento");

    _mainLayout->addWidget(_modifica);
    _mainLayout->addWidget(_elimina);

    connect(_elimina,SIGNAL(clicked()),this,SLOT(OnClickElimina()));
    connect(_modifica,SIGNAL(clicked()),this,SLOT(OnClickModifica()));

}

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

/*view_finestra &view_finestra::operator=(const view_finestra &other)
{
    if (this == &other)
        return *this;

    _model=other._model;
    _ann=other._ann;
    _StatoModifica=other._StatoModifica;
    _mainLayout=other._mainLayout;
    _LineTitolo=other._LineTitolo;
    _LineCorpo=other._LineCorpo;
    _LineDesc=other._LineDesc;
    _calendario=other._calendario;
    _ora=other._ora;
    _TableList=other._TableList;
    _tipo=other._tipo;
    _elimina=other._elimina;
    _modifica=other._modifica;
    return *this;
}*/

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
        _LineDesc->setEnabled(_boolean);
        _TableList->setEnabled(_boolean);
    }
    if(dynamic_cast<spesa*>(_ann))
    {
        _LineDesc->setEnabled(_boolean);
        _TableList->setEnabled(_boolean);
    }
}

annotazione* view_finestra::ReadChangedValues()
{
    if(dynamic_cast<spesa*>(_ann) )
    {
        return new spesa(_LineTitolo->text(),_LineDesc->document()->toRawText());
    }
    else if (dynamic_cast<elenco*>(_ann) )
    {
        return new elenco(_LineTitolo->text(),_LineDesc->document()->toRawText());
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

void view_finestra::closeEvent(QCloseEvent *event)
{
    //if (tabellaModel->deviSalvare())
    //{
    //    checkUnsavedData();
    //}
    emit ClosedWindow();
    event->accept();
}

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

void view_finestra::OnClickElimina()
{
    qDebug() <<"dainviare";
    emit Eliminato();
    qDebug() <<"inviato?";
    _model->rimouviElemento(_ann);
}


