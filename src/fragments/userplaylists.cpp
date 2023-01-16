#include "userplaylists.h"
#include "ui_userplaylists.h"
#include <QVBoxLayout>

UserPlaylists::UserPlaylists(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::UserPlaylists) {
    ui->setupUi(this);
}

UserPlaylists::~UserPlaylists() {
    delete ui;
}

void UserPlaylists::setUser(Poco::SharedPtr <BaseModel> model) {
    m_user = model.cast<UserModel>();
}

void UserPlaylists::update() {
    if (!m_user.isNull()) {
        ui->scrollArea->setVisible(true);
        QFrame *frame = new QFrame();
        QVBoxLayout *l = new QVBoxLayout(frame);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(frame);

        try {
            auto playlists = m_user->m_userBase->getUserLibrary()->getOwnPlaylists();

            for (int i{}; i < playlists.size(); ++i) {
                QPointer <PlaylistPB> playlistPB = new PlaylistPB(playlists[i], this, m_user);
                l->addWidget(playlistPB);
            }
        } catch (Poco::Exception &ex) {
            std::cerr << ex.message();
        }
    }
}


void UserPlaylists::on_pb_create_clicked() {
    navigateWithUser(screens::CREATE_PLAYLIST_TAG, m_user);
}

