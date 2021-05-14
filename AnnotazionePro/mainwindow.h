#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QCloseEvent>
#include <QInputDialog>
#include "View/Widget/wannotazione.h"
#include <QDebug>
#include <QDesktopWidget>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow()=default;

private:
    //
    QVBoxLayout *mainLayout;
    wAnnotazione *wA;
    //load Data when opening the window
    void loadData();

    void addMenuButtons();

    void setApplicationStyle();

    void checkUnsavedData();

    void closeEvent(QCloseEvent *event);

private slots:
    void apriClicked();
    void salvaClicked();
    void salvaConNomeClicked();
    void esportaStipendio();
    void analizzaStipendio();

};
#endif // MAINWINDOW_H
