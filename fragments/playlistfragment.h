#ifndef PLAYLISTFRAGMENT_H
#define PLAYLISTFRAGMENT_H

#include <QMenu>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QPointer>

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../models/performermodel.h"
#include "../buttons/songpb.h"
#include "../buttons/categorypb.h"
#include "../actions/addsongtoplaylist.h"
#include "../actions/deletesongfromplaylist.h"

namespace Ui
{
    class PlaylistFragment;
}

class PlaylistFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit PlaylistFragment(QWidget *parent = nullptr);

    ~PlaylistFragment();

    void setData(Poco::SharedPtr <DBWorker> model) override;

    void setUser(Poco::SharedPtr <BaseModel> model) override;

    void update() override;

private
    slots:
            void on_pb_changeName_clicked();

    void on_pb_remove_clicked();

    void on_pb_changeCover_clicked();

    void on_RB_Public_clicked(bool checked);

    void on_pb_user_clicked();

private:
    Ui::PlaylistFragment *ui;

    Poco::SharedPtr <Playlist> m_playlist;
    Poco::SharedPtr <BaseModel> m_user;
};

#endif // PLAYLISTFRAGMENT_H
