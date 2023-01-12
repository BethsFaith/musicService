#ifndef USERPLAYLISTS_H
#define USERPLAYLISTS_H

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../MusicBaseData/Objects/headers/Category.h"
#include "ui_categoryfragment.h"
#include "../models/categorymodel.h"
#include "../models/performermodel.h"
#include "../models/playlistmodel.h"
#include "../buttons/categorypb.h"

namespace Ui {
class UserPlaylists;
}

class UserPlaylists : public BaseFragment
{
  Q_OBJECT

      public:
               explicit UserPlaylists(QWidget *parent = nullptr);
  ~UserPlaylists();

 void setUser(Poco::SharedPtr<BaseModel> model) override;
 void setPlaylists(const std::vector<CategoryPB *> &newPlaylists);
 void update() override;
public slots:
  void on_pushButton_clicked();
private slots:
  void on_pb_create_clicked();

private:
  Ui::UserPlaylists *ui;
  Poco::SharedPtr<UserModel> m_user;

  std::vector<CategoryPB*> m_playlists;
};

#endif // USERPLAYLISTS_H
