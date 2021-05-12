#include "mainwindow.h"

#include <QApplication>
#include "Util/lista.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    lista<QString> list;
    for(int i = 0;i<10;i++)
    {
        list.insertFront(QString(i));
    }
    for(int i = 0;i<10;i++)
    {
        qDebug() << list.popFront();
    }



    return a.exec();
}
