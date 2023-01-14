#include "splashfragment.h"
#include "ui_splashfragment.h"
#include <QPicture>
#include <QPixmap>
#include <iostream>
#include <QDebug>
#include "../models/databasemodel.h"

SplashFragment::SplashFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::SplashFragment) {
    ui->setupUi(this);

    keySpace = new QShortcut(this);
    keySpace->setKey(Qt::Key_Space);
    connect(keySpace, SIGNAL(activated()), this, SLOT(slide()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slide()));
}

SplashFragment::~SplashFragment() {
    delete ui;
}

void SplashFragment::slide() {
    Poco::SharedPtr <DataBase> db = Poco::makeShared<DataBase>();
    navigateWithData(screens::START_TAG, db);
}
