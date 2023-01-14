#include "genrepb.h"

GenrePB::GenrePB(Genre &genre, BaseFragment *fragment, Poco::SharedPtr <BaseModel> user, QWidget *parent) :
        BasePicturePB(parent), m_genre{genre}, m_fragment{fragment}, m_user{user} {
    connect(this, &BasePicturePB::clicked, this, &GenrePB::onClicked);
    setName(m_genre.name().c_str());
    setPicture(m_genre.cover_art().c_str());
}

void GenrePB::onClicked() {
    if (m_user.isNull())
        m_fragment->navigateWithData(screens::GENRE_TAG, Poco::makeShared<Genre>(m_genre));
    else
        m_fragment->navigateWithDataAndUser(screens::GENRE_TAG, Poco::makeShared<Genre>(m_genre), m_user);
}

const Genre &GenrePB::genre() const {
    return m_genre;
}
