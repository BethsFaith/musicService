#include "performerstartfragment.h"
#include "ui_performerstartfragment.h"

PerformerStartFragment::PerformerStartFragment(QWidget *parent) :
                                                                  BaseFragment(parent),
                                                                  ui(new Ui::PerformerStartFragment)
{
  ui->setupUi(this);
  container = ui->stackedWidget;

  this->factory = new ScreensFactory(screens::CATALOG_TAG);
  this->navigator = new Navigator(
      this->container,
      this->factory
      );
}

PerformerStartFragment::~PerformerStartFragment()
{
  delete ui;
}

void PerformerStartFragment::setUser(Poco::SharedPtr<BaseModel> model)
{
  auto m = model;
  m_perf = m.cast<PerformerModel>();
}

void PerformerStartFragment::on_pb_exit_clicked()
{
  back();
}

void PerformerStartFragment::on_pb_myCatalog_clicked()
{
   navigator->newRootScreen(screens::PERFORMER_TAG, nullptr, m_perf);
}

void PerformerStartFragment::on_pb_seacrh_clicked()
{
  navigator->newRootScreen(screens::SEARCH_TAG, nullptr, m_perf);
}

void PerformerStartFragment::on_pb_catalog_clicked()
{
  navigator->newRootScreen(screens::CATALOG_TAG, nullptr, m_perf);
}

