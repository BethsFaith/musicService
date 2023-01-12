#ifndef USERSTARTFRAGMENT_H
#define USERSTARTFRAGMENT_H

#include "../base/basefragment.h"
#include "../models/usermodel.h"

#include "../models/databasemodel.h"
#include <QStackedWidget>
#include "../common/screenfactory.h"
#include "../common/navigator.h"

namespace Ui {
class UserStartFragment;
}

class UserStartFragment : public BaseFragment
{
  Q_OBJECT
public:
  explicit UserStartFragment(QWidget *parent = nullptr);
  ~UserStartFragment();

  void setUser(Poco::SharedPtr<BaseModel> model) override;
private slots:
  void on_pb_catalog_clicked();

  void on_pb_seacrh_clicked();

  void on_pb_myCatalog_clicked();

  void on_pb_exit_clicked();

private:
  Ui::UserStartFragment *ui;
  Poco::SharedPtr<UserModel> m_user;

  Poco::SharedPtr<DataBase> m_bm;
  QStackedWidget *container;
  BaseScreensFactory *factory;
  Navigator *navigator;
};

#endif // USERSTARTFRAGMENT_H
