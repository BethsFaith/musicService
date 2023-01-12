#include "playlistpb.h"
#include "ui_playlistpb.h"

playlistPB::playlistPB(QWidget *parent) :
                                          QWidget(parent),
                                          ui(new Ui::playlistPB)
{
  ui->setupUi(this);
}

playlistPB::~playlistPB()
{
  delete ui;
}
