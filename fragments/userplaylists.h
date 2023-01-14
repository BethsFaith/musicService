#ifndef USERPLAYLISTS_H
#define USERPLAYLISTS_H

#include <QPointer>

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../MusicBaseData/Objects/headers/Category.h"
#include "../models/performermodel.h"
#include "../buttons/playlistpb.h"

namespace Ui
{
    class UserPlaylists;
}

class UserPlaylists: public BaseFragment
{
    Q_OBJECT

public:
    explicit UserPlaylists(QWidget *parent = nullptr);

    ~UserPlaylists();

    void setUser(Poco::SharedPtr <BaseModel> model) override;

    void update() override;

private
    slots:
            void on_pb_create_clicked();

private:
    Ui::UserPlaylists *ui;
    Poco::SharedPtr <UserModel> m_user;

    std::vector<PlaylistPB *> m_playlists;
};

#endif // USERPLAYLISTS_H
