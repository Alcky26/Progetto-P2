#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);

    setMinimumSize(1280,720);

    _File = nullptr;
    // Aggiunge bottoni in alto a Sinistra
    addMenuButtons();
    // Dichiarazione wAnnotazione e ModelAnnotazione
    model = new model_annotazione();
    viewA= new view_annotazione(model);

    // Aggiunta di viewAnnotazione al mainLayout
    mainLayout->addWidget(viewA);
    setApplicationStyle();
    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete viewA;
    delete mainLayout;
    delete _File;
    delete model;

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

    connect(apri, SIGNAL(triggered()), this, SLOT(openClicked()));
    connect(salva, SIGNAL(triggered()), this, SLOT(salvaClicked()));
    connect(salvaConNome, SIGNAL(triggered()), this, SLOT(saveNameClicked()));
    connect(chiudi, SIGNAL(triggered()), this, SLOT(close()));

    file->addAction(apri);
    file->addAction(salva);
    file->addAction(salvaConNome);
    file->addAction(chiudi);

    // Creo Menu
    QMenu* _helpMenu = new QMenu("Aiuto", menuBar);

    // Creo Azioni
    QAction* _info = new QAction("Informazioni",_helpMenu);
    QAction* _aboutUs = new QAction("Creatori",_helpMenu);

    // Creo Sottomenu con azioni
    QMenu* _help = new QMenu("Come utilizzare questo Software",_helpMenu);
    QAction* _file = new QAction("Operazioni da/su File",_help);
    QAction* _newEl = new QAction("Creazione nuovo Elemento",_help);
    QAction* _modEl = new QAction("Modifica di un Elemento Esistente",_help);

    // Associo Actions
    connect(_info,SIGNAL(triggered()),this,SLOT(openInfos()));
    connect(_aboutUs,SIGNAL(triggered()),this,SLOT(openAboutUs()));

    connect(_file,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(_newEl,SIGNAL(triggered()),this,SLOT(openNew()));
    connect(_modEl,SIGNAL(triggered()),this,SLOT(openMod()));

    _helpMenu->addAction(_info);
    _helpMenu->addMenu(_help);
    _helpMenu->addAction(_aboutUs);

    _help->addAction(_file);
    _help->addAction(_newEl);
    _help->addAction(_modEl);

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

void MainWindow::checkUnsavedData()
{
    if(model->deviSalvare())
    {
        QMessageBox::StandardButton response= QMessageBox::question(this, "Salvare i dati?", "Vuoi salvare i dati modificati prima di continuare?", QMessageBox::No | QMessageBox::Yes , QMessageBox::Yes);
        if(response == QMessageBox::Yes)
        {
            salvaClicked();
            QMessageBox::information(this, "File salvato","Il File è stato salvato correttamente!");
        }
    }
}

void MainWindow::openClicked()
{
    checkUnsavedData();

    QString filter = "XML File (*.xml)";
    QString fileName = QFileDialog::getOpenFileName(this, "Seleziona un file da importare", QDir::homePath(), filter);

    if(!fileName.isEmpty())
    {
        _File = new QFile(fileName);
        QDomDocument documentoLetto("Documento");
        if(!_File->open(QIODevice::ReadWrite | QIODevice::Text) || !documentoLetto.setContent(_File))
        {
            QMessageBox::information(this, "Impossibile aprire il file", _File->errorString());
            return;
        }
        _File->close();
        try
        {
            model->readFromFile(documentoLetto);
            viewA->ApriGriglia();
        }
        catch (std::exception *e)
        {
            model->reset();
            model->salvato();
            QMessageBox::warning(this, "Impossibile leggere il file", e->what());
        }
    }
}

void MainWindow::salvaClicked()
{
    if (_File != nullptr)
    {
       if(!_File->open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
       {
           QMessageBox::information(this, "Impossibile salvare nel file", _File->errorString());
           return;
       }
       if(_File->fileName().endsWith(".xml"))
       {
           QDomDocument annotazioni = model->saveFile();
           QTextStream stream(_File);
           stream << annotazioni.toString();
           _File->close();
           model->salvato();
       }
    }
    else
    {
       MainWindow::saveNameClicked();
    }
}

void MainWindow::saveNameClicked()
{
    QString filter = "XML File (*.xml)";
    QString fileName = QFileDialog::getSaveFileName(this, "Salva con nome", QDir::homePath(), filter);

    if(!fileName.isEmpty())
    {
       delete _File;
       _File = new QFile(fileName);
       if(!_File->open(QIODevice::ReadWrite | QIODevice::Text))
       {
           QMessageBox::information(this, "Impossibile salvare nel file", _File->errorString());
           return;
       }
       QDomDocument annotazioni = model->saveFile();
       QTextStream stream(_File);
       stream << annotazioni.toString();
       _File->close();
       model->salvato();
    }
}

void MainWindow::openInfos() const
{
    QMessageBox box(QMessageBox::Information, "Informazione", QString("Questo Software può essere utilizzato per gestire le proprie annotazioni"), QMessageBox::Ok);
    box.exec();
}

void MainWindow::openFile() const
{
    QMessageBox box(QMessageBox::Information, "Tutorial", QString("Per aprire un file, utilizzare l'opzione <b>File -> Apri</b> in alto a sinistra.<br>"
                                                                ), QMessageBox::Ok);
    box.exec();
}

void MainWindow::openMod() const
{
    QMessageBox box(QMessageBox::Information, "Tutorial", QString("Per modificare un elemento, cliccare sull'elemento che si desidera modificare."), QMessageBox::Ok);
    box.exec();
}

void MainWindow::openNew() const
{
    QMessageBox box(QMessageBox::Information, "Tutorial", QString("Per creare un nuovo elemento interagire con l'area <b>Inserimento</b>.<br>"
                                                                "Gli elementi creati verrano mostrati nella griglia centrale."), QMessageBox::Ok);
    box.exec();
}

void MainWindow::openAboutUs() const
{
    QMessageBox box(QMessageBox::Information, "Software Made By", QString("Software creato da :         \n Matteo Vignaga       \n Tommaso Berlaffa     "), QMessageBox::Ok);
    box.exec();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(model->deviSalvare())
    {
        QMessageBox::StandardButton response= QMessageBox::question(this, "Salvare i dati?", "Vuoi salvare i dati modificati prima di continuare?", QMessageBox::No | QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Yes);
        if(response == QMessageBox::Yes)
        {
            salvaClicked();
            QMessageBox::information(this, "File salvato","Il File è stato salvato correttamente!");
            event->accept();
            setAttribute(Qt::WA_DeleteOnClose);
        }
        if(response == QMessageBox::Cancel)
            event->ignore();
        if(response == QMessageBox::Close)
            event->ignore();
    }
}


