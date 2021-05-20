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
#include "View/view_annotazione.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QMessageBox>
#include "Model/model_annotazione.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow()=default;

private:
    //
    QVBoxLayout *mainLayout;
    model_annotazione *model;
    view_annotazione *wA;
    //load Data when opening the window
    void loadData();

    void addMenuButtons();

    void setApplicationStyle();

    void checkUnsavedData();

    void closeEvent(QCloseEvent *event);

private slots:
    void openClicked();
    void saveClicked();
    void saveNameClicked();

    // Metodi Per Help!
    void openInfos() const;
    void openHelp() const;
    void openAboutUs() const;

};
#endif // MAINWINDOW_H
