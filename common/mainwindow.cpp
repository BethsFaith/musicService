#include "mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    try {
        container = new QStackedWidget;

        this->factory = new ScreensFactory;
        this->navigator = new Navigator(
                this->container,
                this->factory
        );

        this->resize(1600, 900);
        this->setCentralWidget(container);

    } catch (Poco::Exception &ex) {
        std::cerr << ex.displayText();
    }
}

MainWindow::~MainWindow() {
    delete container;
    delete navigator;
    delete factory;
}
