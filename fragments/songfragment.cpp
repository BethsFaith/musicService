#include "songfragment.h"
#include "ui_songfragment.h"

SongFragment::SongFragment(QWidget *parent) :
                                              BaseFragment(parent),
                                              ui(new Ui::SongFragment)
{
  ui->setupUi(this);
}

SongFragment::~SongFragment()
{
  delete ui;
}
