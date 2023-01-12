#ifndef ALBUMFRAGMENT_H
#define ALBUMFRAGMENT_H

#include <QMenu>
#include <QVBoxLayout>
#include <QFileDialog>

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../models/performermodel.h"
#include "../buttons/songpb.h"
#include "../buttons/categorypb.h"
#include "../actions/addsongtoplaylist.h"
#include "../actions/deletesongfromplaylist.h"

namespace Ui {
class AlbumFragment;
}

class AlbumFragment : public BaseFragment
{
  Q_OBJECT

  public:
explicit AlbumFragment(QWidget *parent = nullptr);
  ~AlbumFragment();

void setData(Poco::SharedPtr<DBWorker> model) override;
void setUser(Poco::SharedPtr<BaseModel> model) override;
void update() override;

public slots:
void on_like_clicked();
void on_name_clicked();
void on_perf_clicked();

private slots:
void on_pb_perf_clicked();

private:
  Ui::AlbumFragment *ui;
  Poco::SharedPtr<Album> m_album;
  Poco::SharedPtr<BaseModel> m_user;

  std::vector<SongPB*> m_songs;
};

#endif // ALBUMFRAGMENT_H
