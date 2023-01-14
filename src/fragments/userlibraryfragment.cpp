#include "userlibraryfragment.h"
#include "ui_userlibraryfragment.h"

UserLibraryFragment::UserLibraryFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::UserLibraryFragment) {
    ui->setupUi(this);
    ui->pb_category->setVisible(false);
}

UserLibraryFragment::~UserLibraryFragment() {
    delete ui;
}

void UserLibraryFragment::setUser(Poco::SharedPtr <BaseModel> model) {
    auto m = model;
    m_user = m.cast<UserModel>();

    if (!m_user.isNull())
        if (m_user->m_userBase->isModerator())
            ui->pb_category->setVisible(true);
}

void UserLibraryFragment::on_pb_favourites_clicked() {
    navigateWithUser(screens::USER_FAVOURITES_TAG, m_user);
}


void UserLibraryFragment::on_pb_category_clicked() {
}


void UserLibraryFragment::on_pb_playlists_clicked() {
    navigateWithUser(screens::USER_PLAYLISTS_TAG, m_user);
}

