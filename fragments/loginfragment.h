#ifndef LOGINFRAGMENT_H
#define LOGINFRAGMENT_H

#include "../base/basefragment.h"
#include "../models/databasemodel.h"
#include "../models/usermodel.h"
#include "../models/performermodel.h"

namespace Ui {
class LoginFragment;
}

class LoginFragment : public BaseFragment
{
  Q_OBJECT

public:
  explicit LoginFragment(QWidget *parent = nullptr);
  ~LoginFragment();

  void setData(Poco::SharedPtr<DBWorker> model) override;
private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::LoginFragment *ui;
  Poco::SharedPtr<DataBase> m_bm;
};

#endif // LOGINFRAGMENT_H
