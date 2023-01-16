#include "addsongtoplaylist.h"

addSongToPlaylist::addSongToPlaylist(QString text, QObject *parent) : QAction(text, parent) {
    connect(this, &QAction::triggered, this, &addSongToPlaylist::action);
}

Poco::SharedPtr <UserModel> addSongToPlaylist::user() {
    return m_user;
}

void addSongToPlaylist::setUser(Poco::SharedPtr <UserModel> newUser) {
    m_user = newUser;
}

int addSongToPlaylist::idSong() {
    return m_idSong;
}

void addSongToPlaylist::setIdSong(int newIdSong) {
    m_idSong = newIdSong;
}

void addSongToPlaylist::action() {
    m_plForm = Poco::makeShared<PlaylistsForm>();
    m_plForm->setUser(m_user);
    m_plForm->setIdSong(m_idSong);
    m_plForm->showWindow();
}
