#ifndef DELETESONGFROMALBUM_H
#define DELETESONGFROMALBUM_H

#include <QAction>
#include "../MusicBaseData/Objects/headers/Album.h"

class deleteSongFromAlbum: public QAction
{
public:
    explicit deleteSongFromAlbum(QString string, int idSong, Album &album, QObject *parent = nullptr);

    signals:
            void completed(int
    idSong);
private:
    void action();

    Album m_album;
    int m_idSong;
};

#endif // DELETESONGFROMALBUM_H
