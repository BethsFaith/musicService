#ifndef SONGPB_H
#define SONGPB_H

#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <Poco/SharedPtr.h>

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../models/performermodel.h"
#include "../MusicBaseData/Objects/headers/Song.h"

namespace Ui
{
    class SongPB;
}

class SongPB: public QWidget
{
    Q_OBJECT

public:
    explicit SongPB(Song &song, BaseFragment *, Poco::SharedPtr <BaseModel> m_user = nullptr,
                    QWidget *parent = nullptr);

    ~SongPB();

    QPushButton *getNameB();

    QPushButton *getPerfB();

    QPushButton *getLikeB();

    Poco::SharedPtr <QMenu> getMenu();

    void setActionToMenu(QAction *action);

    void removeAction(QAction *action);

    void clearMenu();

    const Song &getSong() const;

private slots:
    void on_pb_perf_clicked();

    void on_pb_name_clicked();

    void on_pb_like_clicked();

    void on_pb_add_clicked();

private:
    Ui::SongPB *ui;

    Poco::SharedPtr <QMenu> menu;
    Song song;
    Poco::SharedPtr <BaseModel> m_user;
    BaseFragment *m_fragment;
};

#endif // SONGPB_H
