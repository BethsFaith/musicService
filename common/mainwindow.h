#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "screenfactory.h"
#include "navigator.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    QStackedWidget *container;
    Navigator *navigator;
    BaseScreensFactory *factory;
};

#endif // MAINWINDOW_H
