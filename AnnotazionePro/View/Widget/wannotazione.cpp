    #include "wannotazione.h"

wAnnotazione::wAnnotazione(annotazione *ann, QWidget *parent) : QWidget(parent)
{
    _mainBoxLayout = new QVBoxLayout(this);
    _state=0;

    QListWidget *_MainWidgetList= new QListWidget();
    _MainWidgetList->setSizeAdjustPolicy(QListWidget::AdjustToContents);

    QVBoxLayout *_mainVBoxLayout = new QVBoxLayout();

    //varia in base al tipo dinamico di ann
    QGroupBox *_Titolo = new QGroupBox();
    QVBoxLayout *_BoxTitle =new QVBoxLayout();

    // Il Titolo è sempre presente
    _LabTitolo = new QLabel("<b>"+ann->getTitolo()+"</b>");
    _LabTitolo->setFont(QFont( "MS Shell Dlg 2,7.8,-1,5,50,0,0,0,0,0" ));
    _LabTitolo->setAlignment(Qt::AlignCenter);

    _BoxTitle->addWidget(_LabTitolo);
    _Titolo->setLayout(_BoxTitle);
    _mainVBoxLayout->addWidget(_Titolo);



    if(dynamic_cast<promemoria*>(ann))
    {
        promemoria* _prom=dynamic_cast<promemoria*>(ann);
        _LabDateTime = new QLabel("Data : "+_prom->getDate().toString() + "\n"+"Ora : " +  _prom->getTime().toString());
        _mainVBoxLayout->addWidget(_LabDateTime);
    }

    if(dynamic_cast<ricorrenza*>(ann))
    {
        ricorrenza* _ric=dynamic_cast<ricorrenza*>(ann);
        _LabDateTime = new QLabel("Data : "+_ric->getDate().toString() + "\n"+"Ora : " +  _ric->getTime().toString());
        _mainVBoxLayout->addWidget(_LabDateTime);
        _LabRicorrenza = new QLabel( _ric->TipoToQString() );
        _mainVBoxLayout->addWidget(_LabRicorrenza);
    }

    if(dynamic_cast<nota*>(ann))
    {
        nota* _nota=dynamic_cast<nota*>(ann);
        _LabCorpo = new QPlainTextEdit(_nota->getCorpo());
        _LabCorpo->setFrameStyle(1);
        _LabCorpo->setReadOnly(true);
        _LabCorpo->setVerticalScrollBar(new QScrollBar());
        _LabCorpo->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _LabCorpo->setStyleSheet("background:rgb(224, 217, 215);");
        _mainVBoxLayout->addWidget(_LabCorpo);
    }

    if(dynamic_cast<elenco*>(ann) && !dynamic_cast<spesa*>(ann))
    {
        elenco* _ele=dynamic_cast<elenco*>(ann);
        _LabDescrizione = new QLabel(_ele->getDescrizione());
        _mainVBoxLayout->addWidget(_LabDescrizione);
        _LabElenco = new QPlainTextEdit (metodi_extra::ElencoAsText(_ele->getElenco()));
        _LabElenco->setFrameStyle(1);
        _LabElenco->setReadOnly(true);
        _LabElenco->setVerticalScrollBar(new QScrollBar());
        _LabElenco->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _LabElenco->setStyleSheet("background:rgb(224, 217, 215);");
        _mainVBoxLayout->addWidget(_LabElenco);
    }

    if(dynamic_cast<spesa*>(ann))
    {
        spesa* _spe=dynamic_cast<spesa*>(ann);
        _LabDescrizione = new QLabel(_spe->getDescrizione());
        _mainVBoxLayout->addWidget(_LabDescrizione);
        _LabElenco = new QPlainTextEdit(metodi_extra::SpesaAsText(_spe->getSpesa() ));
        _LabElenco->setFrameStyle(1);
        _LabElenco->setReadOnly(true);
        _LabElenco->setVerticalScrollBar(new QScrollBar());
        _LabElenco->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _LabElenco->setStyleSheet("background:rgb(224, 217, 215);");
        _mainVBoxLayout->addWidget(_LabElenco);
        _LabCostoTot = new QLabel("Costo totale: "+QString::number(_spe->CostoComplessivo()));

        _mainVBoxLayout->addWidget(_LabCostoTot);
    }

    _MainWidgetList->setLayout(_mainVBoxLayout);


    _mainBoxLayout->addWidget(_MainWidgetList);

}

wAnnotazione::~wAnnotazione()
{
    delete _mainBoxLayout;
}

void wAnnotazione::mousePressEvent(QMouseEvent *)
{
    _state = 1;
    repaint();
    emit pressed();
}

void wAnnotazione::mouseReleaseEvent(QMouseEvent *)
{
    _state = 0;
    repaint();
    emit released();
    emit clicked();
}

void wAnnotazione::paintEvent(QPaintEvent *)
{
    if(_state)
    {
        _state=0;
        update();
    }
    else
    {
        _state=1;
        update();
    }
}

