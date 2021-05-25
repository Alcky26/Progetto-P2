#include "view_finestra.h"


view_finestra::view_finestra(model_annotazione *model, annotazione *ann, QWidget *parent) : _model(model), QWidget(parent)
{
    _mainLayout = new QHBoxLayout(this);
    //Elementi per Visualizzare
    _LineTitolo= new QLineEdit(ann->getTitolo());

    QPushButton *_elimina,*_modifica;////////////////////////////////////////////////////////////////////////////////////////////////////////

    QFont _TitleFont("Times", 15, QFont::Bold);
    QFont _MainFont("Times", 12);

    if(dynamic_cast<promemoria*>(ann))
    {
        _ora = new QDateTimeEdit(dynamic_cast<promemoria*>(ann)->getTime());
        _calendario = new QCalendarWidget();
        _calendario->setSelectedDate(dynamic_cast<promemoria*>(ann)->getDate());
    }

    if(dynamic_cast<ricorrenza*>(ann))
    {
        _ora = new QDateTimeEdit(dynamic_cast<promemoria*>(ann)->getTime());
        _calendario = new QCalendarWidget();
        _calendario->setSelectedDate(dynamic_cast<promemoria*>(ann)->getDate());
        _tipo = new QComboBox();///////////////////////////////////////////////////////////////////////////////// AGGIUNGI LA SCELTA DI TIPI
    }

    if(dynamic_cast<nota*>(ann))
    {
        _LineCorpo = new QTextEdit(dynamic_cast<nota*>(ann)->getCorpo());
    }

    if(dynamic_cast<elenco*>(ann) && !dynamic_cast<spesa*>(ann))
    {
        _LineDesc = new QTextEdit(dynamic_cast<elenco*>(ann)->getDescrizione());
        int i=0;
        for(lista<type_elenco*>::constiterator ci = dynamic_cast<elenco*>(ann)->getElenco().begin() ; ci!=dynamic_cast<elenco*>(ann)->getElenco().end() ; ci++)
        {
            _TableList->setItem(i,0,new QTableWidgetItem(dynamic_cast<elenco*>(ann)->getElenco().index(ci)->getValue()));
            i++;
        }
        _TableList->setColumnWidth(0,_TableList->width()-20);
        _TableList->setShowGrid(true);
        _TableList->setHorizontalHeaderItem(0,new QTableWidgetItem("Elemento"));
    }

    if(dynamic_cast<spesa*>(ann))
    {
        _LineDesc = new QTextEdit(dynamic_cast<spesa*>(ann)->getDescrizione());
        int i=0;
        for(lista<type_spesa*>::constiterator ci = dynamic_cast<spesa*>(ann)->getSpesa().begin() ; ci!=dynamic_cast<spesa*>(ann)->getSpesa().end() ; ci++)
        {
            _TableList->setItem(i,0,new QTableWidgetItem(dynamic_cast<spesa*>(ann)->getSpesa().index(ci)->getValue()));
            _TableList->setItem(i,1,new QTableWidgetItem(dynamic_cast<spesa*>(ann)->getSpesa().index(ci)->getCost()));
            i++;
        }
        _TableList->setColumnWidth(0,_TableList->width()-20);
        _TableList->setShowGrid(true);
        _TableList->setHorizontalHeaderItem(0,new QTableWidgetItem("Elemento"));
        _TableList->setHorizontalHeaderItem(1,new QTableWidgetItem("Costo"));
    }
}
