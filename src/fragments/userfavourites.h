#ifndef USERFAVOURITES_H
#define USERFAVOURITES_H

#include <QPointer>

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../models/performermodel.h"
#include "../buttons/songpb.h"
#include "../forms/playlistsform.h"
#include "../actions/addsongtoplaylist.h"

#include <QMenu>

namespace Ui
{
    class UserFavourites;
}

class UserFavourites: public BaseFragment
{
    Q_OBJECT

public:
    explicit UserFavourites(QWidget *parent = nullptr);

    ~UserFavourites();

    void setUser(Poco::SharedPtr <BaseModel> model) override;

    void update() override;

private:
    void updateSongs();

    Ui::UserFavourites *ui;
    Poco::SharedPtr <UserModel> m_user;
    Poco::SharedPtr <PlaylistsForm> m_plForm;

    std::vector<SongPB *> m_songs;
};

#endif // USERFAVOURITES_H
