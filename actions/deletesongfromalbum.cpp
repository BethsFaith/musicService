#include "deletesongfromalbum.h"

deleteSongFromAlbum::deleteSongFromAlbum(QString string, int idSong, Album &album, QObject *parent) : QAction(string,
                                                                                                              parent),
                                                                                                      m_idSong{idSong},
                                                                                                      m_album{album} {
    connect(this, &QAction::triggered, this, &deleteSongFromAlbum::action);
}

void deleteSongFromAlbum::action() {
    m_album.removeSong(m_idSong);
}
