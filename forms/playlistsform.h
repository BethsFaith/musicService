#ifndef PLAYLISTSFORM_H
#define PLAYLISTSFORM_H

#include <QWidget>
#include <Poco/SharedPtr.h>
#include <QVBoxLayout>
#include "../models/usermodel.h"
#include "../buttons/playlistpb.h"

namespace Ui
{
    class PlaylistsForm;
}

class PlaylistsForm: public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistsForm(QWidget *parent = nullptr);

    ~PlaylistsForm();

    void setUser(Poco::SharedPtr <UserModel>);

    void setIdSong(int id);

    void showWindow();

private
    slots:
            void on_playlist_clicked();

private:
    Ui::PlaylistsForm *ui;
    Poco::SharedPtr <UserModel> m_user;
    int m_songId;

    std::vector<PlaylistPB *> m_playlists;
};

#endif // PLAYLISTSFORM_H
