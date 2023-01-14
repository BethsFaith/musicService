#ifndef ALBUMFRAGMENT_H
#define ALBUMFRAGMENT_H

#include <QMenu>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QPointer>
#include <QRadioButton>

#include "../MusicBaseData/Objects/headers/SharedLibrary.h"
#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../models/performermodel.h"
#include "../buttons/songpb.h"
#include "../buttons/categorypb.h"
#include "../actions/addsongtoplaylist.h"
#include "../actions/deletesongfromalbum.h"

namespace Ui
{
    class AlbumFragment;
}

class AlbumFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit AlbumFragment(QWidget *parent = nullptr);

    ~AlbumFragment();

    void setData(Poco::SharedPtr <DBWorker> model) override;

    void setUser(Poco::SharedPtr <BaseModel> model) override;

    void update() override;

private
    slots:
            void on_pb_perf_clicked();

    void on_pb_addSong_clicked();

    void on_pb_changeName_clicked();

    void on_pb_changeCover_clicked();

    void on_pb_public_clicked();

    void on_pb_remove_clicked();

    void on_song_removed(int idSong);

private:
    Ui::AlbumFragment *ui;
    Poco::SharedPtr <Album> m_album;
    Poco::SharedPtr <BaseModel> m_user;
    QVBoxLayout *l;

    std::vector<SongPB *> m_songs;
    std::vector<QRadioButton *> m_genres;
};

#endif // ALBUMFRAGMENT_H
