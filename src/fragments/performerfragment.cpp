#include "performerfragment.h"
#include "ui_performerfragment.h"

PerformerFragment::PerformerFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::PerformerFragment) {
    ui->setupUi(this);
    ui->pb_createAlbum->setVisible(false);
}

PerformerFragment::~PerformerFragment() {
    delete ui;
}

void PerformerFragment::setUser(Poco::SharedPtr <BaseModel> model) {
    m_user = model;
}

void PerformerFragment::setData(Poco::SharedPtr <DBWorker> model) {
    m_performer = model.unsafeCast<Performer>();
}

void PerformerFragment::update() {
    if (!m_performer.isNull()) {
        ui->l_name->setText(m_performer->getName().c_str());

        ui->SA_albums->setVisible(true);
        QFrame *frame = new QFrame();
        QVBoxLayout *l = new QVBoxLayout(frame);
        l->setDirection(QVBoxLayout::Direction::LeftToRight);
        ui->SA_albums->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->SA_albums->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->SA_albums->setWidgetResizable(true);
        ui->SA_albums->setWidget(frame);

        try {
            auto albums = m_performer->getAlbums();
            for (int i{}; i < albums.size(); ++i) {
                if (albums[i].isPublic()) {
                    QPointer <AlbumPB> alPB = new AlbumPB(albums[i], this, m_user);
                    l->addWidget(alPB);
                }
            }
        } catch (Poco::Exception &ex) {
            std::cerr << ex.message();
        }

        ui->SA_Songs->setVisible(true);
        QFrame *frame2 = new QFrame();
        QVBoxLayout *l2 = new QVBoxLayout(frame2);
        ui->SA_Songs->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->SA_Songs->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->SA_Songs->setWidgetResizable(true);
        ui->SA_Songs->setWidget(frame2);

        Poco::SharedPtr <UserModel> user;
        if (!m_user.isNull()) {
            user = m_user.cast<UserModel>();
        }

        try {
            auto songs = m_performer->getSongs();
            for (int i{}; i < songs.size(); ++i) {
                QPointer <SongPB> songPB = new SongPB(songs[i], this, m_user);

                if (!user.isNull()) {
                    auto addToPlaylist = new addSongToPlaylist("Добавить в плейлист");
                    addToPlaylist->setUser(user);
                    addToPlaylist->setIdSong(songs[i].getId());
                    songPB->setActionToMenu(addToPlaylist);
                }
                l2->addWidget(songPB);
            }
        } catch (Poco::Exception &ex) {
            std::cerr << ex.message();
        }
    }
}
