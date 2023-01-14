#include "basefragment.h"
#include "ui_basefragment.h"
#include <QVBoxLayout>


BaseFragment::BaseFragment(QWidget *parent) :
        QFrame(parent),
        ui(new Ui::BaseFragment) {
    ui->setupUi(this);
}

BaseFragment::~BaseFragment() {
    delete ui;
}

void BaseFragment::onPause() {}

void BaseFragment::onResume() {}

void BaseFragment::setData(Poco::SharedPtr <DBWorker> model) {}

void BaseFragment::setUser(Poco::SharedPtr <BaseModel> model) {}

void BaseFragment::update() {}

void BaseFragment::clearList(QLayout *list) {
    QLayoutItem *child;
    while (list->count() != 0) {
        child = list->takeAt(0);
        if (child->layout() != 0) {
            clearList(child->layout());
        }
        else if (child->widget() != 0) {
            delete child->widget();
        }
        delete child;
    }
}
