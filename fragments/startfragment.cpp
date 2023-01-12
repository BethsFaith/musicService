#include "startfragment.h"
#include "ui_startfragment.h"

StartFragment::StartFragment(QWidget *parent) :
                                               BaseFragment(parent),
                                                ui(new Ui::StartFragment)
{
  ui->setupUi(this);
  container = ui->stackedWidget;

  this->factory = new ScreensFactory(screens::CATALOG_TAG);
  this->navigator = new Navigator(
      this->container,
      this->factory
      );

  navigator->newRootScreen(screens::CATALOG_TAG);
}

StartFragment::~StartFragment()
{
  delete ui;
}

void StartFragment::setData(Poco::SharedPtr<DBWorker> model)
{
  auto m = model;
  m_bm = m.unsafeCast<DataBase>();
}

void StartFragment::on_pb_catalog_clicked()
{
  navigator->newRootScreen(screens::CATALOG_TAG);
}

void StartFragment::on_pb_search_clicked()
{
//  ui->stackedWidget->setCurrentWidget(new SearchFragment);
//  navigator->newRootScreen(screens::SEARCH_TAG);
}

void StartFragment::on_pb_log_clicked()
{
  navigateWithData(screens::LOGIN_TAG, m_bm);
}

void StartFragment::on_pb_reg_clicked()
{
  navigateWithData(screens::REGISTRATION_TAG, m_bm);
}


void StartFragment::on_pb_seacrh_clicked()
{
    navigator->newRootScreen(screens::SEARCH_TAG, m_bm);
//  auto newFragment = new SearchFragment;
//  ui->stackedWidget->addWidget(newFragment);
//  ui->stackedWidget->setCurrentWidget(newFragment);
}

