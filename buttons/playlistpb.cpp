#include "playlistpb.h"

PlaylistPB::PlaylistPB(Playlist &playlist, BaseFragment *fragment, Poco::SharedPtr <BaseModel> user, QWidget *parent) :
        BasePicturePB(parent),
        m_user{user},
        m_playlist{playlist},
        m_fragment{fragment} {
    connect(this, &BasePicturePB::clicked, this, &PlaylistPB::onClicked);
    setName(m_playlist.getName().c_str());
    setPicture(m_playlist.getCoverArtRef().c_str());
}

void PlaylistPB::onClicked() {
    if (m_user.isNull())
        m_fragment->navigateWithData(screens::PLAYLIST_TAG, Poco::makeShared<Playlist>(m_playlist));
    else
        m_fragment->navigateWithDataAndUser(screens::PLAYLIST_TAG, Poco::makeShared<Playlist>(m_playlist), m_user);
}

Playlist &PlaylistPB::getPlaylist() {
    return m_playlist;
}
