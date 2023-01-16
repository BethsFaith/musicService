#include "startfragment.h"
#include "ui_startfragment.h"

StartFragment::StartFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::StartFragment) {
    ui->setupUi(this);
    container = ui->stackedWidget;

    this->factory = new ScreensFactory(screens::CATALOG_TAG);
    this->navigator = new Navigator(
            this->container,
            this->factory
    );
}

StartFragment::~StartFragment() {
    delete ui;
    delete factory;
    delete navigator;
}

void StartFragment::setData(Poco::SharedPtr <DBWorker> model) {
    m_bm = model.cast<DataBase>();
    try {
        navigator->newRootScreen(screens::CATALOG_TAG, m_bm);
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.displayText();
    }
    catch (std::exception &ex) {
        std::cerr << ex.what();
    }
}

void StartFragment::on_pb_catalog_clicked() {
    navigator->newRootScreen(screens::CATALOG_TAG, m_bm);
}

void StartFragment::on_pb_log_clicked() {
    navigateWithData(screens::LOGIN_TAG, m_bm);
}

void StartFragment::on_pb_reg_clicked() {
    navigateWithData(screens::REGISTRATION_TAG, m_bm);
}

void StartFragment::on_pb_seacrh_clicked() {
    navigator->newRootScreen(screens::SEARCH_TAG, m_bm);
}

