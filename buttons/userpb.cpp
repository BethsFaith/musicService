#include "userpb.h"
#include "ui_userpb.h"

userPB::userPB(QWidget *parent) :
                                  QWidget(parent),
                                  ui(new Ui::userPB)
{
  ui->setupUi(this);
}

userPB::~userPB()
{
  delete ui;
}
