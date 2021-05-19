#include "mainwindow.h"

#include <QApplication>
#include "Util/lista.h"
#include "Data/spesa.h"
#include <QDebug>
#include <string.h>
#include <QString>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setWindowIcon(QIcon("dog.png"));
    a.setApplicationName("Annotazioni");

    MainWindow w;

    w.show();

    return a.exec();
}
