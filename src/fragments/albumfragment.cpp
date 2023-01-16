#include "albumfragment.h"
#include "ui_albumfragment.h"

AlbumFragment::AlbumFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::AlbumFragment) {
    ui->setupUi(this);

    ui->pb_public->setVisible(false);
    ui->pb_changeCover->setVisible(false);
    ui->pb_changeName->setVisible(false);
    ui->pb_remove->setVisible(false);
    ui->LE_name->setReadOnly(true);

    ui->pb_public->setVisible(false);
    ui->pb_addSong->setVisible(false);
    ui->l_genre->setVisible(false);
    ui->l_nameSong->setVisible(false);
    ui->LE_nameSong->setVisible(false);
    ui->l_error->setVisible(false);
    ui->SA_genre->setVisible(false);
}

AlbumFragment::~AlbumFragment() {
    delete ui;
    delete l;
}

void AlbumFragment::setData(Poco::SharedPtr <DBWorker> model) {
    auto m = model;
    m_album = m.cast<Album>();

    ui->LE_name->setText(m_album->getName().c_str());
    ui->pb_perf->setText(m_album->getPerformerNickname().c_str());
    QPixmap picture(m_album->getCoverArtRef().c_str());
    QSize PicSize(200, 200);
    picture = picture.scaled(PicSize, Qt::KeepAspectRatio);
    ui->l_Cover->resize(picture.height(), picture.width());
    ui->l_Cover->setPixmap(picture);
}

void AlbumFragment::setUser(Poco::SharedPtr <BaseModel> model) {
    m_user = model;
}

void AlbumFragment::update() {
    Poco::SharedPtr <UserModel> user;
    Poco::SharedPtr <PerformerModel> perf;
    if (!m_user.isNull()) {
        perf = m_user.cast<PerformerModel>();
        user = m_user.cast<UserModel>();
    }
    if (!perf.isNull())
        if (perf->getPerformer()->getName() == m_album->getPerformerNickname()) {
            ui->pb_changeCover->setVisible(true);
            ui->pb_changeName->setVisible(true);
            ui->pb_remove->setVisible(true);
            ui->LE_name->setReadOnly(false);
            if (!m_album->isPublic()) {
                ui->pb_public->setVisible(true);
                ui->pb_addSong->setVisible(true);
                ui->l_genre->setVisible(true);
                ui->l_nameSong->setVisible(true);
                ui->LE_nameSong->setVisible(true);
                ui->l_error->setVisible(true);
                ui->SA_genre->setVisible(true);

                QFrame *frame = new QFrame();
                QVBoxLayout *l2 = new QVBoxLayout(frame);
                ui->SA_genre->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
                ui->SA_genre->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                ui->SA_genre->setWidgetResizable(true);
                ui->SA_genre->setWidget(frame);
                SharedLibrary shl(perf->getPerformer()->dataBase());

                auto genres = shl.getAllGenres();
                for (const auto &g: genres) {
                    QPointer <QRadioButton> qrb = new QRadioButton();
                    qrb->setText(g.name().c_str());
                    l2->addWidget(qrb);
                    m_genres.push_back(qrb);
                }
            }
        }

    QFrame *frame2 = new QFrame();
    l = new QVBoxLayout(frame2);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(frame2);

    auto songs = m_album->getSongs();
    for (int i{}; i < songs.size(); ++i) {
        m_songs.push_back(new SongPB(songs[i], this, m_user));

        if (!user.isNull()) {
            auto addToPlaylist = new addSongToPlaylist("Добавить в плейлист");
            addToPlaylist->setUser(user);
            addToPlaylist->setIdSong(songs[i].getId());
            m_songs[i]->setActionToMenu(addToPlaylist);
        }
        if (!perf.isNull())
            if (perf->getPerformer()->getName() == m_album->getPerformerNickname() && !m_album->isPublic()) {
                auto deleteSong = new deleteSongFromAlbum("Удалить", songs[i].getId(), *m_album);
                m_songs[i]->setActionToMenu(deleteSong);
            }
        l->addWidget(m_songs[i]);
    }
}


void AlbumFragment::on_pb_perf_clicked() {
    try {
        Poco::SharedPtr <Performer> perf = Poco::makeShared<Performer>(m_album->getPerformerNickname(),
                                                                       m_album->getDB());
        if (m_user.isNull())
            navigateWithData(screens::PERFORMER_TAG, perf);
        else
            navigateWithDataAndUser(screens::PERFORMER_TAG, perf, m_user);
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.message() << std::endl;
    }
}


void AlbumFragment::on_pb_addSong_clicked() {
    std::string genre{};
    for (const auto &r: m_genres)
        if (r->isChecked()) {
            genre = r->text().toStdString();
            r->setChecked(false);
            break;
        }

    if (genre.empty()) {
        ui->l_error->setText("Выберите жанр");
        return;
    }
    std::string name = ui->LE_nameSong->text().toStdString();
    if (name.empty()) {
        ui->l_error->setText("Выберите имя");
        return;
    }
    else if (m_album->getDB()->getSongId(name, m_album->getPerformerNickname()) != 0) {
        ui->l_error->setText("Песня с таким названием и исполнителем уже существует");
        return;
    }
    try {
        m_album->addSong(name, genre);
    } catch (Poco::Exception &ex) {
        ui->l_error->setText("Ошибка при добавлении");
    }
    ui->l_error->setText("");
    ui->LE_nameSong->clear();
    Song s(name, m_album->getPerformerNickname(), m_album->getDB());
    auto spb = new SongPB(s, this, m_user);
    l->addWidget(spb);
    auto deleteSong = new deleteSongFromAlbum("Удалить", s.getId(), *m_album);
    spb->setActionToMenu(deleteSong);
}


void AlbumFragment::on_pb_changeName_clicked() {
    auto name = ui->LE_name->text().toStdString();
    m_album->setName(name);
}


void AlbumFragment::on_pb_changeCover_clicked() {
    try {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "/home",
                                                        tr("Images (*.png *.xpm *.jpg)"));
        if (!fileName.isEmpty()) {
            m_album->setCoverArt(fileName.toStdString());
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


void AlbumFragment::on_pb_public_clicked() {
    m_album->toPublish();
    ui->pb_public->setVisible(false);
    ui->pb_addSong->setVisible(false);
    ui->l_genre->setVisible(false);
    ui->l_nameSong->setVisible(false);
    ui->LE_nameSong->setVisible(false);
    ui->l_error->setVisible(false);
    ui->SA_genre->setVisible(false);
}


void AlbumFragment::on_pb_remove_clicked() {
    Poco::SharedPtr <PerformerModel> perf;
    perf = m_user.cast<PerformerModel>();
    perf->getPerformer()->removeAlbum(m_album->getName());
    navigateWithUser(screens::PERFTOOLS_TAG, m_user);
}

void AlbumFragment::on_song_removed(int idSong) {
}
