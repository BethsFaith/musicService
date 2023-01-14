#include "createplaylistfragment.h"
#include "ui_createplaylistfragment.h"

CreatePlaylistFragment::CreatePlaylistFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::CreatePlaylistFragment) {
    ui->setupUi(this);
}

CreatePlaylistFragment::~CreatePlaylistFragment() {
    delete ui;
}

void CreatePlaylistFragment::setUser(Poco::SharedPtr <BaseModel> model) {
    auto m = model;
    m_user = m.cast<UserModel>();
}

void CreatePlaylistFragment::on_pb_create_clicked() {
    std::string name = ui->TE_Name->toPlainText().toStdString();
    if (name.empty()) {
        ui->l_error->setText(QString{"Не оставляйте поля пустыми"});
        return;
    }

    m_user->m_userBase->getDataBase()->insertPlaylist(name, m_user->m_userBase->getNick(), file,
                                                      ui->cb_isPublic->isChecked());
    Poco::SharedPtr <Playlist> pl = Poco::makeShared<Playlist>(m_user->m_userBase->getNick(), name,
                                                               m_user->m_userBase->getDataBase());
    navigateWithDataAndUser(screens::PLAYLIST_TAG, pl, m_user);
}


void CreatePlaylistFragment::on_pb_picture_clicked() {
    try {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "/home",
                                                        tr("Images (*.png *.xpm *.jpg)"));
        if (!fileName.isEmpty()) {
            file = fileName.toStdString();
            QPixmap picture(fileName);
            QSize PicSize(200, 200);
            picture = picture.scaled(PicSize, Qt::KeepAspectRatio);
            ui->l_coverArt->resize(picture.height(), picture.width());
            ui->l_coverArt->setPixmap(picture);
        }
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.displayText();
    }
}

