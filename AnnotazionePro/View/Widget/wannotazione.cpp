#include "wannotazione.h"

wAnnotazione::wAnnotazione(annotazione *ann, QWidget *parent) : QWidget(parent)
{
    _mainBoxLayout = new QVBoxLayout(this);

    _state=0;

    //setAttribute(Qt::WA_Hover);


    QListWidget *_Scatola= new QListWidget();
    _Scatola->setSizeAdjustPolicy(QListWidget::AdjustToContents);

    QVBoxLayout *_mainVBoxLayout = new QVBoxLayout();

    //varia in base al tipo dynamico di ann
    QGroupBox *_Titolo = new QGroupBox();
    QVBoxLayout *_BoxTitle =new QVBoxLayout();


    _LabTitolo = new QLabel(ann->getTitolo());
    _LabTitolo->setAlignment(Qt::AlignCenter);
    _BoxTitle->addWidget(_LabTitolo);
    _Titolo->setLayout(_BoxTitle);
    _mainVBoxLayout->addWidget(_Titolo);


    if(dynamic_cast<promemoria*>(ann))
    {
        _LabDateTime = new QLabel("Data : "+dynamic_cast<promemoria*>(ann)->getDate().toString() + "\n"+"Ora : " +  dynamic_cast<promemoria*>(ann)->getTime().toString());
        _mainVBoxLayout->addWidget(_LabDateTime);
    }

    if(dynamic_cast<ricorrenza*>(ann))
    {
        _LabDateTime = new QLabel("Data : "+dynamic_cast<ricorrenza*>(ann)->getDate().toString() + "\n"+"Ora : " +  dynamic_cast<ricorrenza*>(ann)->getTime().toString());
        _mainVBoxLayout->addWidget(_LabDateTime);
        _LabRicorrenza = new QLabel(dynamic_cast<ricorrenza*>(ann)->typeToQString());
        _mainVBoxLayout->addWidget(_LabRicorrenza);
    }

    if(dynamic_cast<nota*>(ann))
    {
        _LabCorpo = new QPlainTextEdit(dynamic_cast<nota*>(ann)->getCorpo());
        _LabCorpo->setFrameStyle(1);
        _LabCorpo->setReadOnly(true);
        _LabCorpo->setVerticalScrollBar(new QScrollBar());
        _LabCorpo->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _LabCorpo->setStyleSheet("background:rgb(224, 217, 215);");
        _mainVBoxLayout->addWidget(_LabCorpo);
    }

    if(dynamic_cast<elenco*>(ann) && !dynamic_cast<spesa*>(ann))
    {
        _LabDescrizione = new QLabel(dynamic_cast<elenco*>(ann)->getDescrizione());
        _mainVBoxLayout->addWidget(_LabDescrizione);

        _LabElenco = new QPlainTextEdit (dynamic_cast<elenco*>(ann)->getListAsText());
        _LabElenco->setFrameStyle(1);
        _LabElenco->setReadOnly(true);
        _LabElenco->setVerticalScrollBar(new QScrollBar());
        _LabElenco->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _mainVBoxLayout->addWidget(_LabElenco);
    }

    if(dynamic_cast<spesa*>(ann))
    {
        _LabDescrizione = new QLabel(dynamic_cast<spesa*>(ann)->getDescrizione());
        _mainVBoxLayout->addWidget(_LabDescrizione);

        _LabElenco = new QPlainTextEdit(dynamic_cast<spesa*>(ann)->getListSpesaAsText());
        _LabElenco->setFrameStyle(1);
        _LabElenco->setReadOnly(true);
        _LabElenco->setVerticalScrollBar(new QScrollBar());
        _LabElenco->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _mainVBoxLayout->addWidget(_LabElenco);

    }

    _Scatola->setLayout(_mainVBoxLayout);

    _mainBoxLayout->addWidget(_Scatola);

}

wAnnotazione::~wAnnotazione()
{
    delete _mainBoxLayout;
    delete  _LabCorpo;
    delete _corpoScroll;
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

void wAnnotazione::aggiornaValori(annotazione* ann)
{
    _LabTitolo->setText(ann->getTitolo());

    if(dynamic_cast<promemoria*>(ann))
    {
        _LabDateTime->setText("Data : "+dynamic_cast<promemoria*>(ann)->getDate().toString() + "\n"+"Ora : " +  dynamic_cast<promemoria*>(ann)->getTime().toString());
    }
    if(dynamic_cast<ricorrenza*>(ann))
    {
        _LabDateTime->setText("Data : "+dynamic_cast<ricorrenza*>(ann)->getDate().toString() + "\n"+"Ora : " +  dynamic_cast<ricorrenza*>(ann)->getTime().toString());
        //_LabRicorrenza->setFont(_MainFont);
    }
    if(dynamic_cast<nota*>(ann))
    {
        _LabCorpo->document()->setPlainText( dynamic_cast<nota*>(ann)->getCorpo());
    }
    if(dynamic_cast<elenco*>(ann) && !dynamic_cast<spesa*>(ann))
    {
        _LabDescrizione->setText(dynamic_cast<elenco*>(ann)->getDescrizione());

        _LabElenco->document()->setPlainText( dynamic_cast<elenco*>(ann)->getListAsText());
    }
    if(dynamic_cast<spesa*>(ann))
    {
        _LabDescrizione->setText(dynamic_cast<spesa*>(ann)->getDescrizione());
        _LabElenco->document()->setPlainText( dynamic_cast<spesa*>(ann)->getListSpesaAsText());
    }

}

