#include "playlistfragment.h"
#include "ui_playlistfragment.h"

PlaylistFragment::PlaylistFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::PlaylistFragment) {
    ui->setupUi(this);
    ui->RB_Public->setVisible(false);
    ui->pb_changeCover->setVisible(false);
    ui->pb_remove->setVisible(false);
    ui->pb_changeName->setVisible(false);
    ui->LE_name->setReadOnly(true);
}

PlaylistFragment::~PlaylistFragment() {
    delete ui;
}

void PlaylistFragment::setData(Poco::SharedPtr <DBWorker> model) {
    auto m = model;
    m_playlist = m.unsafeCast<Playlist>();

    ui->LE_name->setText(m_playlist->getName().c_str());
    ui->pb_user->setText(m_playlist->getUserNickname().c_str());
    QPixmap picture(m_playlist->getCoverArtRef().c_str());
    QSize PicSize(290, 290);
    picture = picture.scaled(PicSize, Qt::KeepAspectRatio);
    ui->l_Cover->setPixmap(picture);
}

void PlaylistFragment::setUser(Poco::SharedPtr <BaseModel> model) {
    m_user = model;
}

void PlaylistFragment::update() {
    try {
        Poco::SharedPtr <UserModel> user;
        if (!m_user.isNull()) {
            user = m_user.cast<UserModel>();
            if (!user.isNull())
                if (m_playlist->getUserNickname() == user->m_userBase->getNick()) {
                    ui->RB_Public->setVisible(true);
                    ui->pb_changeCover->setVisible(true);
                    ui->pb_changeName->setVisible(true);
                    ui->pb_remove->setVisible(true);
                    ui->LE_name->setReadOnly(false);
                    ui->RB_Public->setChecked(m_playlist->isPublic());
                }
        }

        QFrame *frame = new QFrame();
        QVBoxLayout *l = new QVBoxLayout(frame);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(frame);

        auto songs = m_playlist->getSongs();
        for (int i{}; i < songs.size(); ++i) {
            QPointer<SongPB> songPB = new SongPB(songs[i], this, m_user);

            l->addWidget(songPB);

            if (!user.isNull()) {
                if (m_playlist->getUserNickname() == user->m_userBase->getNick()) {
                    auto remove = new deleteSongFromPlaylist("Удалить из плейлиста");
                    remove->setPlaylist(m_playlist);
                    remove->setIdSong(songs[i].getId());
                    songPB->clearMenu();
                    songPB->setActionToMenu(remove);
                }
                else {
                    auto addToPlaylist = new addSongToPlaylist("Добавить в плейлист");
                    addToPlaylist->setUser(user);
                    addToPlaylist->setIdSong(songs[i].getId());
                    songPB->setActionToMenu(addToPlaylist);
                }
            }
        }
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.displayText() << std::endl;
    }
}

void PlaylistFragment::on_pb_changeName_clicked() {
    try {
        auto name = ui->LE_name->text();
        m_playlist->setName(name.toStdString());
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.displayText();
    }
}


void PlaylistFragment::on_pb_remove_clicked() {
    m_playlist->getDb()->deletePlaylist(m_playlist->getId());
    backWithUser(m_user);
}

void PlaylistFragment::on_pb_changeCover_clicked() {
    try {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "/home",
                                                        tr("Images (*.png *.xpm *.jpg)"));
        if (!fileName.isEmpty()) {
            m_playlist->setCoverArt(fileName.toStdString());
            QPixmap picture(fileName);
            QSize PicSize(200, 200);
            picture = picture.scaled(PicSize, Qt::KeepAspectRatio);
            ui->l_Cover->setPixmap(picture);
        }
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.displayText();
    }
}


void PlaylistFragment::on_RB_Public_clicked(bool checked) {
    m_playlist->setPublic(checked);
}

void PlaylistFragment::on_pb_user_clicked() {
    try {
        Poco::SharedPtr <User> user = Poco::makeShared<User>(m_playlist->getUserNickname(), m_playlist->getDb());
        if (m_user.isNull())
            navigateWithData(screens::USER_TAG, user);
        else
            navigateWithDataAndUser(screens::USER_TAG, user, m_user);
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.message() << std::endl;
    }
}

