#ifndef SEARCHFRAGMENT_H
#define SEARCHFRAGMENT_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPointer>
#include <QWidget>

#include "../base/basefragment.h"
#include "../../MusicBaseData/Objects/headers/SharedLibrary.h"
#include "../buttons/songpb.h"
#include "../buttons/categorypb.h"
#include "../buttons/albumpb.h"
#include "../buttons/playlistpb.h"
#include "../models/usermodel.h"
#include "../models/performermodel.h"
#include "../actions/addsongtoplaylist.h"


namespace Ui
{
    class SearchFragment;
}

enum ButtonsId
{
    SONGS,
    PLAYLISTS,
    USERS,
    ALBUMS,
    PERFORMERS,
};

class SearchFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit SearchFragment(QWidget *parent = nullptr);

    ~SearchFragment();

    void setData(Poco::SharedPtr <DBWorker> model) override;

    void setUser(Poco::SharedPtr <BaseModel> model) override;

    void update() override;

private
    slots:
            void on_LE_browser_editingFinished();

    void clickedUser();

    void clickedPerformer();

private:
    void updateSongs();

    void updatePerformers();

    void updateUsers();

    void updateAlbums();

    void updatePlaylists();

    Ui::SearchFragment *ui;

    QButtonGroup *m_groupBox;
    QFrame *m_frame;
    QVBoxLayout *m_layout;

    Poco::SharedPtr <SharedLibrary> m_sharedLib;
    Poco::SharedPtr <BaseModel> m_baseM;
    Poco::SharedPtr <UserModel> m_user;

    std::vector<SongPB *> m_songs;

    std::vector<QWidget *> m_searchableButtons;
};

#endif // SEARCHFRAGMENT_H
