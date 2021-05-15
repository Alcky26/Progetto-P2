#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    // Aggiunge bottoni in alto a Sinistra
    addMenuButtons();
    // Modifica Dimensioni e Margini
    setApplicationStyle();

    // Da aggiungere
    //
    // Dichiarazione wAnnotazione e ModelAnnotazione
    //  Model = new ModelAnnotazione();
    //  wAnn = new wAnnotazione(Model);
    //
    // Aggiunta di wAnnotazione al mainLayout
    //  mainLayout->addWidget(wAnn);

    //setLayout(mainLayout);
}

void MainWindow::addMenuButtons()
{
    QMenuBar* menuBar = new QMenuBar(this);

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

    connect(apri, SIGNAL(triggered()), this, SLOT(apriClicked()));
    connect(salva, SIGNAL(triggered()), this, SLOT(salvaClicked()));
    connect(salvaConNome, SIGNAL(triggered()), this, SLOT(salvaConNomeClicked()));
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
    connect(_info,SIGNAL(triggered()),this,SLOT(apriInfos()));
    connect(_help,SIGNAL(triggered()),this,SLOT(apriHelp()));
    connect(_aboutUs,SIGNAL(triggered()),this,SLOT(apriAboutUs()));

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

void MainWindow::apriClicked()
{

}

void MainWindow::salvaClicked()
{

}

void MainWindow::salvaConNomeClicked()
{

}

void MainWindow::apriInfos() const
{
    QMessageBox box(QMessageBox::Information, "Info", QString("Informazioni - "), QMessageBox::Ok);
    box.exec();
}

void MainWindow::apriHelp() const
{
    QMessageBox box(QMessageBox::Information, "Help", QString("Help - "), QMessageBox::Ok);
    box.exec();
}

void MainWindow::apriAboutUs() const
{
    QMessageBox box(QMessageBox::Information, "About Us", QString("About Us - "), QMessageBox::Ok);
    box.exec();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //serve il Model

}


