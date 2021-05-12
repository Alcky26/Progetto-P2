#include "mainwindow.h"

#include <QApplication>
#include "Util/lista.h"
#include <QDebug>
#include <string.h>
#include <QString>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    return a.exec();
}
