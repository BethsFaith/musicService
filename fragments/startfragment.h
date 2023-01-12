#ifndef STARTFRAGMENT_H
#define STARTFRAGMENT_H

#include "../base/basefragment.h"
#include <Poco/SharedPtr.h>
#include "../models/databasemodel.h"
#include <QStackedWidget>
#include "../common/screenfactory.h"
#include "../common/navigator.h"

namespace Ui {
class StartFragment;
}

class StartFragment : public BaseFragment
{
  Q_OBJECT

public:
explicit StartFragment(QWidget *parent = nullptr);
  ~StartFragment();

void setData(Poco::SharedPtr<DBWorker> model) override;

private slots:
   void on_pb_catalog_clicked();

   void on_pb_search_clicked();

   void on_pb_log_clicked();

   void on_pb_reg_clicked();

   void on_pb_seacrh_clicked();

 private:
  Ui::StartFragment *ui;
  Poco::SharedPtr<DataBase> m_bm;
  QStackedWidget *container;
  BaseScreensFactory *factory;
  Navigator *navigator;
};

#endif // STARTFRAGMENT_H
