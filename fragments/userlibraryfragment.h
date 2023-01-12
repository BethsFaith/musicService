#ifndef USERLIBRARYFRAGMENT_H
#define USERLIBRARYFRAGMENT_H

#include "../base/basefragment.h"
#include "../models/usermodel.h"

namespace Ui {
class UserLibraryFragment;
}

class UserLibraryFragment : public BaseFragment
{
  Q_OBJECT

public:
  explicit UserLibraryFragment(QWidget *parent = nullptr);
  ~UserLibraryFragment();
    void setUser(Poco::SharedPtr<BaseModel> model) override;
private slots:

  void on_pb_favourites_clicked();

  void on_pb_category_clicked();

  void on_pb_playlists_clicked();

private:
  Ui::UserLibraryFragment *ui;
  Poco::SharedPtr<UserModel> m_user;
};

#endif // USERLIBRARYFRAGMENT_H
