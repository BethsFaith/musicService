#include "loginfragment.h"
#include "ui_loginfragment.h"

LoginFragment::LoginFragment(QWidget *parent) :
                                                BaseFragment(parent),
                                                ui(new Ui::LoginFragment)
{
  ui->setupUi(this);
}

LoginFragment::~LoginFragment()
{
  delete ui;
}

void LoginFragment::setData(Poco::SharedPtr<DBWorker> model)
{
  auto m = model;
  m_bm = m.unsafeCast<DataBase>();
}

void LoginFragment::on_pushButton_clicked()
{
  std::string login = ui->TE_Login->toPlainText().toStdString();
  std::string pass = ui->TE_Pass->toPlainText().toStdString();
  if (login.empty() || pass.empty())
    {
      ui->l_error->setText(QString{"Не оставляйте поля пустыми"});
      return;
    }

  if (m_bm->checkUserPass(login, pass))
  {
    int id = m_bm->getUserIdByLogin(login);
    Poco::SharedPtr<User> user = Poco::makeShared<User>(id, m_bm);
    Poco::SharedPtr<UserModel> userM = Poco::makeShared<UserModel>(user);
    std::cout << "user:" << userM << std::endl;
    navigateWithUser(screens::START_USER_TAG, userM);
  }
  else if (m_bm->checkPerformerPass(login, pass))
  {
    int id = m_bm->getPerformerIdByLogin(login);
    Poco::SharedPtr<Performer> performer = Poco::makeShared<Performer>(id, m_bm);
    Poco::SharedPtr<PerformerModel> performerM = Poco::makeShared<PerformerModel>(performer);
    navigateWithUser(screens::START_PERF_TAG, performerM);
  }
  else
  {
    ui->l_error->setText(QString{"Неверный логин или пароль"});
    return;
  }
}

void LoginFragment::on_pushButton_2_clicked()
{
  backWithData(m_bm);
}

