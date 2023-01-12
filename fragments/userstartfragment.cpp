#include "userstartfragment.h"
#include "ui_userstartfragment.h"

UserStartFragment::UserStartFragment(QWidget *parent) :
                                                        BaseFragment(parent),
                                                        ui(new Ui::UserStartFragment)
{
  ui->setupUi(this);

  container = ui->stackedWidget;

  this->factory = new ScreensFactory(screens::CATALOG_TAG);
  this->navigator = new Navigator(
      this->container,
      this->factory
      );

  std::cout << m_user << "user <<" << std::endl;
}

UserStartFragment::~UserStartFragment()
{
  delete ui;
}

void UserStartFragment::setUser(Poco::SharedPtr<BaseModel> model)
{
//  std::cout << "model:" << model << std::endl;
  auto m = model;
  m_user = m.cast<UserModel>();

  ui->l_nameUser->setText(QString((" " + m_user->m_userBase->getNick()).c_str()));
}

void UserStartFragment::on_pb_catalog_clicked()
{
   navigator->newRootScreen(screens::CATALOG_TAG, nullptr, m_user);
}


void UserStartFragment::on_pb_seacrh_clicked()
{
  try{
    navigator->newRootScreen(screens::SEARCH_TAG, m_user->m_userBase->getDataBase(), m_user);
  }
  catch(Poco::Exception &ex)
  {
    std::cout << ex.displayText();
  }
}


void UserStartFragment::on_pb_myCatalog_clicked()
{
//   std::cout << "CLICKED" << std::endl;
   navigator->newRootScreen(screens::USER_LIBRARY_TAG, nullptr, m_user);
}


void UserStartFragment::on_pb_exit_clicked()
{
//  std::cout << "CLICKED" << std::endl;
  back();
}

