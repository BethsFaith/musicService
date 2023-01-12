#ifndef CATEGORYFRAGMENT_H
#define CATEGORYFRAGMENT_H

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../MusicBaseData/Objects/headers/Category.h"
#include "ui_categoryfragment.h"
#include "../models/categorymodel.h"
#include "../models/performermodel.h"
#include "../models/playlistmodel.h"
#include "../buttons/categorypb.h"

namespace Ui {
class CategoryFragment;
}

class CategoryFragment : public BaseFragment
{
  Q_OBJECT

  public:
explicit CategoryFragment(QWidget *parent = nullptr);
  ~CategoryFragment();

  void setData(Poco::SharedPtr<DBWorker> model) override;
  void setUser(Poco::SharedPtr<BaseModel> model) override;
  void update() override;
public slots:
  void on_pushButton_clicked();

private:
  Ui::CategoryFragment *ui;
  Poco::SharedPtr<Category> m_category;
  Poco::SharedPtr<BaseModel> m_user;
//  Poco::SharedPtr<UserModel> m_user;
//  Poco::SharedPtr<PerformerModel> m_performer;

  std::vector<CategoryPB*> m_playlists;
};

#endif // CATEGORYFRAGMENT_H
