#include "albumpb.h"


AlbumPB::AlbumPB(Album &album, BaseFragment *fragment, Poco::SharedPtr <BaseModel> user, QWidget *parent) :
        BasePicturePB(parent), m_album{album}, m_user{user}, m_fragment{fragment} {
    connect(this, &BasePicturePB::clicked, this, &AlbumPB::onClicked);
    setName(m_album.getName().c_str());
    setPicture(m_album.getCoverArtRef().c_str());
}

void AlbumPB::onClicked() {
    if (m_user.isNull())
        m_fragment->navigateWithData(screens::ALBUM_TAG, Poco::makeShared<Album>(m_album));
    else
        m_fragment->navigateWithDataAndUser(screens::ALBUM_TAG, Poco::makeShared<Album>(m_album), m_user);
}

const Album &AlbumPB::album() const {
    return m_album;
}
