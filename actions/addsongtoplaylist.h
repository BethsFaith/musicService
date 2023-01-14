#ifndef ADDSONGTOPLAYLIST_H
#define ADDSONGTOPLAYLIST_H

#include <QAction>
#include "../models/usermodel.h"
#include "../forms/playlistsform.h"

class addSongToPlaylist: public QAction
{
public:
    explicit addSongToPlaylist(QString string, QObject *parent = nullptr);

    virtual ~addSongToPlaylist() = default;

    Poco::SharedPtr <UserModel> user();

    void setUser(Poco::SharedPtr <UserModel> newUser);

    int idSong();

    void setIdSong(int newIdSong);

public slots:
    void action();

private:
    Poco::SharedPtr <UserModel> m_user;
    int m_idSong;
    Poco::SharedPtr <PlaylistsForm> m_plForm;
};

#endif // ADDSONGTOPLAYLIST_H
