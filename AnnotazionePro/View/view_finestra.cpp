#include "view_finestra.h"


view_finestra::view_finestra(model_annotazione *model, annotazione *ann, QWidget *parent) : QWidget(parent),  _model(model)
{
    _mainLayout = new QVBoxLayout(this);

    // Titolo
    _LineTitolo= new QLineEdit();
    _LineTitolo->setText(ann->getTitolo());
    _LineTitolo->setEnabled(false);
    _mainLayout->addWidget(_LineTitolo);

    // Futuri Bottoni
    ///QPushButton *_elimina,*_modifica;///

    // Font Estemporaneo
    QFont _TitleFont("Times", 15, QFont::Bold);
    QFont _MainFont("Times", 12);

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
        _TableList->setVisible(false);
        _mainLayout->addWidget(_TableList);
    }
}


