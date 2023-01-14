#include "createsongfragment.h"
#include "ui_createsongfragment.h"

CreateSongFragment::CreateSongFragment(QWidget *parent) :
        QFrame(parent),
        ui(new Ui::CreateSongFragment) {
    ui->setupUi(this);
}

CreateSongFragment::~CreateSongFragment() {
    delete ui;
}
