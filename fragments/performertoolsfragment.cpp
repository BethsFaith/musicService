#include "performertoolsfragment.h"
#include "ui_performertoolsfragment.h"

PerformerToolsFragment::PerformerToolsFragment(QWidget *parent) :
                                                                  BaseFragment(parent),
                                                                  ui(new Ui::PerformerToolsFragment)
{
  ui->setupUi(this);

}

PerformerToolsFragment::~PerformerToolsFragment()
{
  delete ui;
}
