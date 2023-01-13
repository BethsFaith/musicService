#include "basepicturepb.h"
#include "ui_basepicturepb.h"

BasePicturePB::BasePicturePB(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::BasePicturePB) {
    ui->setupUi(this);
}

BasePicturePB::~BasePicturePB() {
    delete ui;
}

void BasePicturePB::setName(const QString &name) {
    ui->l_name->setText(name);
}

void BasePicturePB::setPicture(const QString &fileName) {
    QPixmap pixmap(fileName);
    QIcon ButtonIcon(pixmap);
    ui->pushButton->setIcon(ButtonIcon);
    ui->pushButton->setIconSize(pixmap.rect().size());
}

void BasePicturePB::on_pushButton_clicked() {
    emit clicked();
}

