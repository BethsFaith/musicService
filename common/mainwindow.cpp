#include "mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  try {
    container = new QStackedWidget;

    this->factory = new ScreensFactory;
    this->navigator = new Navigator(
        this->container,
        this->factory
        );

//    QString mainStyle = "QWidget#window {"
//                        "background-color:#EFF5FC;"
//                        "}";
//    container->setStyleSheet(mainStyle);
//    container->setObjectName("window");

//    this->resize(QDesktopWidget().availableGeometry(this).size()*1);
    this->resize(1600,900);
    this->setCentralWidget(container);

  } catch (Poco::Exception &ex) {
    std::cout << ex.displayText();
  }
}

MainWindow::~MainWindow() {
  delete container;
  delete navigator;
  delete factory;
}
