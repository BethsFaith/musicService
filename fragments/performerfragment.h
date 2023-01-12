#ifndef PERFORMERFRAGMENT_H
#define PERFORMERFRAGMENT_H

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../MusicBaseData/Persons/headers/Performer.h"
#include "ui_categoryfragment.h"
#include "../models/categorymodel.h"
#include "../models/performermodel.h"
#include "../models/playlistmodel.h"
#include "../buttons/categorypb.h"
#include "../buttons/songpb.h"
#include "../actions/addsongtoplaylist.h"

namespace Ui {
class PerformerFragment;
}

class PerformerFragment : public BaseFragment
{
  Q_OBJECT

      public:
explicit PerformerFragment(QWidget *parent = nullptr);
  ~PerformerFragment();
  void setUser(Poco::SharedPtr<BaseModel> model) override;
  void setData(Poco::SharedPtr<DBWorker> model) override;
  void update() override;

public slots:
  void on_album_clicked();
  void on_like_clicked();
  void on_name_clicked();
  void on_perf_clicked();
private:
  Ui::PerformerFragment *ui;

  Poco::SharedPtr<Performer> m_performer;
  Poco::SharedPtr<BaseModel> m_user;

  std::vector<CategoryPB*> m_albums;
  std::vector<SongPB*> m_songs;
};

#endif // PERFORMERFRAGMENT_H
