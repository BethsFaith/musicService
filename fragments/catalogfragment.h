#ifndef CATALOGFRAGMENT_H
#define CATALOGFRAGMENT_H

#include "../base/basefragment.h"
#include "../models/categorymodel.h"
#include "../models/usermodel.h"
#include "../models/databasemodel.h"
#include "../MusicBaseData/Objects/headers/SharedLibrary.h"
#include "../buttons/categorypb.h"
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class CatalogFragment;
}

class CatalogFragment : public BaseFragment
{
  Q_OBJECT

      public:
explicit CatalogFragment(QWidget *parent = nullptr);
  ~CatalogFragment();

  void setUser(Poco::SharedPtr<BaseModel> model) override;
public slots:
  void on_category_clicked();
  void on_genre_clicked();
private:
  Ui::CatalogFragment *ui;
  Poco::SharedPtr<DataBase> m_bm;
  Poco::SharedPtr<SharedLibrary> m_slib;
  std::vector<CategoryPB*> m_categories;
  std::vector<CategoryPB*> m_genres;
//  Poco::SharedPtr<UserModel> m_user;
  Poco::SharedPtr<BaseModel> m_user;
  QVBoxLayout *l;
  QVBoxLayout *l2;
};

#endif // CATALOGFRAGMENT_H
