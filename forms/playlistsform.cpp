#include "playlistsform.h"
#include "ui_playlistsform.h"

PlaylistsForm::PlaylistsForm(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::PlaylistsForm) {
    ui->setupUi(this);
}

PlaylistsForm::~PlaylistsForm() {
    delete ui;
}

void PlaylistsForm::setUser(Poco::SharedPtr <UserModel> _user) {
    m_user = _user;
}

void PlaylistsForm::setIdSong(int id) {
    m_songId = id;
}

void PlaylistsForm::showWindow() {
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
            m_playlists.push_back(new PlaylistPB(playlists[i], nullptr));

            disconnect(m_playlists.at(i), &BasePicturePB::clicked, m_playlists.at(i), &PlaylistPB::onClicked);
            connect(m_playlists.at(i), &BasePicturePB::clicked, this, &PlaylistsForm::on_playlist_clicked);

            l->addWidget(m_playlists[i]);

            this->show();
        }
    } catch (Poco::Exception &ex) {
        std::cout << ex.message();
    }
}

void PlaylistsForm::on_playlist_clicked() {
    PlaylistPB *button = qobject_cast<PlaylistPB *>(sender());
    int id{};
    if (button != NULL) {
        try {
            button->getPlaylist().addSong(m_songId);
        }
        catch (Poco::Exception &ex) {
            std::cout << ex.displayText() << std::endl;
        }
    }
}
