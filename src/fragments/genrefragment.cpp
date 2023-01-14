#include "genrefragment.h"
#include "ui_genrefragment.h"

GenreFragment::GenreFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::GenreFragment) {
    ui->setupUi(this);
    ui->pb_changeCover->setVisible(false);
    ui->pb_changeName->setVisible(false);
    ui->LE_name->setReadOnly(true);
}

GenreFragment::~GenreFragment() {
    delete ui;
}

void GenreFragment::setData(Poco::SharedPtr <DBWorker> model) {
    auto m = model;
    m_genre = m.unsafeCast<Genre>();
}

void GenreFragment::setUser(Poco::SharedPtr <BaseModel> model) {
    m_user = model;
    auto user = m_user.cast<UserModel>();

    if (!user.isNull())
        if (user->m_userBase->isModerator()) {
            ui->pb_changeCover->setVisible(true);
            ui->pb_changeName->setVisible(true);
            ui->LE_name->setReadOnly(false);
        }
}

void GenreFragment::update() {
    if (!m_genre.isNull()) {
        ui->LE_name->setText(m_genre->name().c_str());

        QPixmap picture(m_genre->cover_art().c_str());
        QSize PicSize(200, 200);

        picture = picture.scaled(PicSize, Qt::KeepAspectRatio);
        ui->l_Cover->resize(picture.height(), picture.width());
        ui->l_Cover->setPixmap(picture);

        QFrame *frame = new QFrame();
        QVBoxLayout *l = new QVBoxLayout(frame);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(frame);

        Poco::SharedPtr <UserModel> user;
        if (!m_user.isNull())
            user = m_user.cast<UserModel>();

        auto songs = m_genre->getSongs();
        for (int i{}; i < songs.size(); ++i) {
            QPointer <SongPB> songPB = new SongPB(songs[i], this, m_user);
            if (!user.isNull()) {
                auto addToPlaylist = new addSongToPlaylist("Добавить в плейлист");
                addToPlaylist->setUser(user);
                addToPlaylist->setIdSong(songs[i].getId());
                songPB->setActionToMenu(addToPlaylist);
            }
            l->addWidget(songPB);
        }
    }
}

void GenreFragment::on_pb_changeCover_clicked() {
    try {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "/home",
                                                        tr("Images (*.png *.xpm *.jpg)"));
        if (!fileName.isEmpty()) {
            m_genre->setCover_art(fileName.toStdString());
            QPixmap picture(fileName);
            QSize PicSize(200, 200);
            picture = picture.scaled(PicSize, Qt::KeepAspectRatio);
            ui->l_Cover->resize(picture.height(), picture.width());
            ui->l_Cover->setPixmap(picture);
        }
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.displayText();
    }
}

void GenreFragment::on_pb_changeName_clicked() {
    try {
        auto name = ui->LE_name->text();
        m_genre->setName(name.toStdString());
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.displayText();
    }
}

