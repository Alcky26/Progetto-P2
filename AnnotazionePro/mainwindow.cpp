#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);

    _File = nullptr;
    // Aggiunge bottoni in alto a Sinistra
    addMenuButtons();
    // Dichiarazione wAnnotazione e ModelAnnotazione
    model = new model_annotazione();
    wA= new view_annotazione(model);


    //
    // Aggiunta di wAnnotazione al mainLayout
    mainLayout->addWidget(wA);
    setApplicationStyle();
    setLayout(mainLayout);
}

void MainWindow::addMenuButtons()
{
    QMenuBar* menuBar = new QMenuBar(this);

    menuBar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);

    QMenu* file = new QMenu("File", menuBar);

    QAction* apri = new QAction("Apri", file);
    apri->setShortcut(Qt::CTRL | Qt::Key_O);

    QAction* salva = new QAction("Salva", file);
    salva->setShortcut(Qt::CTRL | Qt::Key_S);

    QAction* salvaConNome = new QAction("Salva con nome", file);
    salvaConNome->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);
    QAction* chiudi = new QAction("Chiudi", file);

    /*QAction* esportaStipendio = new QAction("Esporta stipendi", file);
    esportaStipendio->setShortcut(Qt::CTRL | Qt::Key_E);
    QAction* analizzaStipendio = new QAction("Analizza stipendio", file);
    analizzaStipendio->setShortcut(Qt::CTRL | Qt::Key_A);*/

    connect(apri, SIGNAL(triggered()), this, SLOT(openClicked()));
    connect(salva, SIGNAL(triggered()), this, SLOT(saveClicked()));
    connect(salvaConNome, SIGNAL(triggered()), this, SLOT(saveNameClicked()));
    connect(chiudi, SIGNAL(triggered()), this, SLOT(close()));
    /*connect(esportaStipendio, SIGNAL(triggered()), this, SLOT(esportaStipendio()));
    connect(analizzaStipendio, SIGNAL(triggered()), this, SLOT(analizzaStipendio()));
    */

    file->addAction(apri);
    file->addAction(salva);
    file->addAction(salvaConNome);
    file->addAction(chiudi);
    /*file->addAction(esportaStipendio);
    file->addAction(analizzaStipendio);
    */

    // ORA FACCIO IO HELP HAHAHAHAHA

    // Creo Menu
    QMenu* _helpMenu = new QMenu("Help!", menuBar);
    // Creo Azioni
    QAction* _info = new QAction("Infos",_helpMenu);
    QAction* _help = new QAction("How to",_helpMenu);
    QAction* _aboutUs = new QAction("About us",_helpMenu);
    // Associo Actions
    connect(_info,SIGNAL(triggered()),this,SLOT(openInfos()));
    connect(_help,SIGNAL(triggered()),this,SLOT(openHelp()));
    connect(_aboutUs,SIGNAL(triggered()),this,SLOT(openAboutUs()));

    _helpMenu->addAction(_info);
    _helpMenu->addAction(_help);
    _helpMenu->addAction(_aboutUs);

    menuBar->addMenu(file);
    menuBar->addMenu(_helpMenu);

    mainLayout->addWidget(menuBar);
}

void MainWindow::setApplicationStyle()
{
    setWindowState(Qt::WindowMaximized);
    setMinimumSize(QSize(500,500));
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    mainLayout->setMargin(0);
}

void MainWindow::openClicked()
{
    QString _Filter = "XML File (**.xml)";
    QString _FileName = QFileDialog::getOpenFileName(this, "Seleziona un file da importare",QDir::homePath(),_Filter);

    if(!_FileName.isEmpty()){
        _File = new QFile(_FileName);
       // QDomDocument documentoLetto("Documento");

    }


}

void MainWindow::saveClicked()
{

}

void MainWindow::saveNameClicked()
{

}

void MainWindow::openInfos() const
{
    QMessageBox box(QMessageBox::Information, "Info", QString("Informazioni - "), QMessageBox::Ok);
    box.exec();
}

void MainWindow::openHelp() const
{
    QMessageBox box(QMessageBox::Information, "Help", QString("Help - "), QMessageBox::Ok);
    box.exec();
}

void MainWindow::openAboutUs() const
{
    QMessageBox box(QMessageBox::Information, "About Us", QString("About Us - "), QMessageBox::Ok);
    box.exec();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //serve il Model
    event->setAccepted(true);
}


