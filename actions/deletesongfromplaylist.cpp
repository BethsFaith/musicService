#include "deletesongfromplaylist.h"

deleteSongFromPlaylist::deleteSongFromPlaylist(QString string, QObject *parent) : QAction(string, parent) {
    connect(this, &QAction::triggered, this, &deleteSongFromPlaylist::action);
}

deleteSongFromPlaylist::~deleteSongFromPlaylist() {
}

void deleteSongFromPlaylist::action() {
    try {
        m_playlist->removeSong(m_idSong);
    }
    catch (Poco::Exception &ex) {
        std::cout << ex.displayText();
    }
}

int deleteSongFromPlaylist::idSong() {
    return m_idSong;
}

void deleteSongFromPlaylist::setIdSong(int newIdSong) {
    std::cout << "newSong!" << newIdSong;
    m_idSong = newIdSong;
}

Poco::SharedPtr <Playlist> deleteSongFromPlaylist::playlist() {
    return m_playlist;
}

void deleteSongFromPlaylist::setPlaylist(Poco::SharedPtr <Playlist> newPlaylist) {
    std::cout << "newPlaylist!" << newPlaylist->getName();
    m_playlist = newPlaylist;
}
