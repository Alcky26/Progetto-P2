#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);

    addMenuButtons();
    setApplicationStyle();

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
    QAction* esportaStipendio = new QAction("Esporta stipendi", file);
    esportaStipendio->setShortcut(Qt::CTRL | Qt::Key_E);
    QAction* analizzaStipendio = new QAction("Analizza stipendio", file);
    analizzaStipendio->setShortcut(Qt::CTRL | Qt::Key_A);
    QAction* chiudi = new QAction("Chiudi", file);

    connect(apri, SIGNAL(triggered()), this, SLOT(apriClicked()));
    connect(salva, SIGNAL(triggered()), this, SLOT(salvaClicked()));
    connect(salvaConNome, SIGNAL(triggered()), this, SLOT(salvaConNomeClicked()));
    connect(esportaStipendio, SIGNAL(triggered()), this, SLOT(esportaStipendio()));
    connect(analizzaStipendio, SIGNAL(triggered()), this, SLOT(analizzaStipendio()));
    connect(chiudi, SIGNAL(triggered()), this, SLOT(close()));

    file->addAction(apri);
    file->addAction(salva);
    file->addAction(salvaConNome);
    file->addAction(esportaStipendio);
    file->addAction(analizzaStipendio);
    file->addAction(chiudi);

    menuBar->addMenu(file);

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

void MainWindow::esportaStipendio()
{

}

void MainWindow::analizzaStipendio()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{

}


