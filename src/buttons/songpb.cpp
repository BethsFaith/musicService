#include "songpb.h"
#include "ui_songpb.h"
#include "../actions/addsongtoplaylist.h"

SongPB::SongPB(Song &_song, BaseFragment *fragment, Poco::SharedPtr <BaseModel> _user, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SongPB),
        song{_song},
        m_fragment{fragment},
        m_user{_user} {
    ui->setupUi(this);
    menu = Poco::makeShared<QMenu>(this);
    ui->pb_add->setVisible(false);
    ui->pb_like->setVisible(false);
    ui->pb_add->setMenu(menu);
    ui->pb_perf->setText(song.getPerformerName().c_str());
    ui->pb_name->setText(song.getName().c_str());

    if (!m_user.isNull()) {
        auto user = m_user.cast<UserModel>();
        if (!user.isNull()) {
            ui->pb_add->setVisible(true);
            ui->pb_like->setVisible(true);

            if (song.isLiked(user->m_userBase->getLogin()))
                ui->pb_like->setText("-");
        }
        else {
            auto perf = m_user.cast<PerformerModel>();
            if (!perf.isNull())
                ui->pb_add->setVisible(true);
        }
    }
}

SongPB::~SongPB() {
    delete ui;
}

QPushButton *SongPB::getNameB() {
    return ui->pb_name;
}

QPushButton *SongPB::getPerfB() {
    return ui->pb_perf;
}

QPushButton *SongPB::getLikeB() {
    return ui->pb_like;
}

void SongPB::on_pb_perf_clicked() {
    try {
        Poco::SharedPtr <Performer> perf = Poco::makeShared<Performer>(song.getPerformerId(), song.dataBase());
        if (m_user.isNull())
            m_fragment->navigateWithData(screens::PERFORMER_TAG, perf);
        else
            m_fragment->navigateWithDataAndUser(screens::PERFORMER_TAG, perf, m_user);
    }
}

void SongPB::on_pb_name_clicked() {
    try {
        Poco::SharedPtr <Album> album = Poco::makeShared<Album>(song.getAlbumName(), song.getPerformerName(),
                                                                song.dataBase());
        if (m_user.isNull())
            m_fragment->navigateWithData(screens::ALBUM_TAG, album);
        else
            m_fragment->navigateWithDataAndUser(screens::ALBUM_TAG, album, m_user);
    }
}

void SongPB::on_pb_like_clicked() {
    try {
        Poco::SharedPtr <UserModel> user;
        if (!m_user.isNull())
            user = m_user.unsafeCast<UserModel>();
        if (user.isNull())
            return;

        if (ui->pb_like->text() == "+")
            user->m_userBase->rateSong(song.getId(), true);
        else
            user->m_userBase->rateSong(song.getId(), false);

        if (song.isLiked(user->m_userBase->getLogin()))
            ui->pb_like->setText("-");
        else
            ui->pb_like->setText("+");
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.message() << std::endl;
    }
}

void SongPB::on_pb_add_clicked() {
    ui->pb_add->showMenu();
}

const Song &SongPB::getSong() const {
    return song;
}

Poco::SharedPtr <QMenu> SongPB::getMenu() {
    return menu;
}

void SongPB::setActionToMenu(QAction *action) {
    menu->addAction(action);
}

void SongPB::removeAction(QAction *action) {
    menu->removeAction(action);
}

void SongPB::clearMenu() {
    menu->clear();
}

