#ifndef PLAYLISTPB_H
#define PLAYLISTPB_H

#include <QWidget>
#include <QPushButton>

#include "../base/basepicturepb.h"
#include "../../MusicBaseData/Objects/headers/Playlist.h"

class PlaylistPB: public BasePicturePB
{
    Q_OBJECT

public:
    explicit PlaylistPB(Playlist &playlist, BaseFragment *fragment, Poco::SharedPtr <BaseModel> m_user = nullptr,
                        QWidget *parent = nullptr);

    ~PlaylistPB() = default;

    Playlist &getPlaylist();

public slots:
    void onClicked();

private:
    Playlist m_playlist;
    Poco::SharedPtr <BaseModel> m_user;
    BaseFragment *m_fragment;
};

#endif // PLAYLISTPB_H
