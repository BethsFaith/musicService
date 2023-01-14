#ifndef BASEFRAGMENT_H
#define BASEFRAGMENT_H

#include <QFrame>
#include <Poco/SharedPtr.h>
#include "basemodel.h"
#include "../../MusicBaseData/General/headers/DBWorker.h"

namespace Ui
{
    class BaseFragment;
}

namespace screens
{
    static const QString SPLASH_TAG = "splash";
    static const QString START_TAG = "start";
    static const QString LOGIN_TAG = "login";
    static const QString REGISTRATION_TAG = "registration";
    static const QString START_USER_TAG = "startuser";
    static const QString START_PERF_TAG = "startperf";
    static const QString CATALOG_TAG = "catalog";
    static const QString SEARCH_TAG = "search";

    static const QString CATEGORY_TAG = "category";
    static const QString PLAYLIST_TAG = "playlists";
    static const QString SONG_TAG = "song";
    static const QString PERFORMER_TAG = "performer";
    static const QString USER_TAG = "user";
    static const QString ALBUM_TAG = "album";
    static const QString USER_FAVOURITES_TAG = "favourites";
    static const QString USER_PLAYLISTS_TAG = "playlistsUser";
    static const QString USER_LIBRARY_TAG = "userlibrary";
    static const QString CREATE_PLAYLIST_TAG = "crplay";

    static const QString GENRE_TAG = "genre";
    static const QString PERFTOOLS_TAG = "perftools";
    static const QString CREATE_ALBUM_TAG = "cralbum";
};

class BaseFragment: public QFrame
{
    Q_OBJECT
    signals:
    void back();

    void navigateTo(QString tag);

    void newRootScreen(QString tag, Poco::SharedPtr <DBWorker> data, Poco::SharedPtr <BaseModel> model);

    void replace(QString tag);

    void navigateWithData(QString tag, Poco::SharedPtr <DBWorker> model);

    void navigateWithUser(QString tag, Poco::SharedPtr <BaseModel> user);

    void backWithData(Poco::SharedPtr <DBWorker>);

    void backWithUser(Poco::SharedPtr <BaseModel> model);

    void navigateWithDataAndUser(QString tag, Poco::SharedPtr <DBWorker> model, Poco::SharedPtr <BaseModel> user);

public:
    explicit BaseFragment(QWidget *parent = nullptr);

    ~BaseFragment();

    virtual void onPause();

    virtual void onResume();

    virtual void setData(Poco::SharedPtr <DBWorker> model);

    void clearList(QLayout *list);

    virtual void setUser(Poco::SharedPtr <BaseModel> model);

    virtual void update();

private:
    Ui::BaseFragment *ui;
};

#endif // BASEFRAGMENT_H
