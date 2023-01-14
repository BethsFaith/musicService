#include "userfragment.h"
#include "ui_userfragment.h"

UserFragment::UserFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::UserFragment) {
    ui->setupUi(this);
}

UserFragment::~UserFragment() {
    delete ui;
}

void UserFragment::setUser(Poco::SharedPtr <BaseModel> model) {
    m_ghostUser = model;
}

void UserFragment::setData(Poco::SharedPtr <DBWorker> model) {
    m_mainUser = model.unsafeCast<User>();
}

void UserFragment::update() {
    if (!m_mainUser.isNull()) {
        ui->l_name->setText(m_mainUser->getNick().c_str());

        ui->scrollArea->setVisible(true);
        QFrame *frame = new QFrame();
        QVBoxLayout *l = new QVBoxLayout(frame);
        l->setDirection(QVBoxLayout::Direction::LeftToRight);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(frame);

        try {
            auto playlists = m_mainUser->getPlaylists();
            for (int i{}; i < playlists.size(); ++i) {
                QPointer <PlaylistPB> playlistPB = new PlaylistPB(playlists[i], this, m_ghostUser);
                l->addWidget(playlistPB);
            }
        } catch (Poco::Exception &ex) {
            std::cerr << ex.message();
        }
    }
}
