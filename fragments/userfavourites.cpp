#include "userfavourites.h"
#include "ui_userfavourites.h"
#include <QVBoxLayout>

UserFavourites::UserFavourites(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::UserFavourites) {
    ui->setupUi(this);
}

UserFavourites::~UserFavourites() {
    delete ui;
}

void UserFavourites::setUser(Poco::SharedPtr <BaseModel> model) {
    auto m = model;
    m_user = m.cast<UserModel>();

    std::cout << "USER FAV" << m_user << std::endl;
}

void UserFavourites::update() {
    if (!m_user.isNull()) {
        QFrame *frame = new QFrame();
        QVBoxLayout *l = new QVBoxLayout(frame);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(frame);

        auto songs = m_user->m_userBase->getUserLibrary()->getSongs();
        for (int i{}; i < songs.size(); ++i) {
            QPointer <SongPB> songPB = new SongPB(songs[i], this, m_user);

            auto addToPlaylist = new addSongToPlaylist("Добавить в плейлист");
            addToPlaylist->setUser(m_user);
            addToPlaylist->setIdSong(songs[i].getId());
            songPB->setActionToMenu(addToPlaylist);

            l->addWidget(songPB);
        }
    }
}
