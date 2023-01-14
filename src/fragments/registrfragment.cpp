#include "registrfragment.h"
#include "ui_registrfragment.h"

RegistrFragment::RegistrFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::RegistrFragment) {
    ui->setupUi(this);
}

RegistrFragment::~RegistrFragment() {
    delete ui;
}

void RegistrFragment::setData(Poco::SharedPtr <DBWorker> model) {
    auto m = model;
    m_bm = m.unsafeCast<DataBase>();
}

void RegistrFragment::on_pushButton_clicked() {
    try {
        Poco::SharedPtr<BaseModel> modele;
        std::string login = ui->TE_Login->toPlainText().toStdString();
        std::string pass = ui->TE_Pass->toPlainText().toStdString();
        std::string nick = ui->TE_Nick->toPlainText().toStdString();
        if (login.empty() || pass.empty() || nick.empty()) {
            ui->l_error->setText(QString{"Не оставляйте поля пустыми"});
            return;
        }

        if (ui->RB_User->isChecked()) {
            int id{};
            id = m_bm->getUserIdByLogin(login);
            id += m_bm->getPerformerIdByLogin(login);
            if (id != 0) {
                ui->l_error->setText(QString{"Пользователь с таким логином уже существует"});
                return;
            }
            id = m_bm->getUserIdByNickname(nick);
            id += m_bm->getPerformerIdByNickname(nick);
            if (id != 0) {
                ui->l_error->setText(QString{"Пользователь с таким никнеймом уже существует"});
                return;
            }

            m_bm->insertUser(login, nick, pass);
            Poco::SharedPtr <User> user = Poco::makeShared<User>(nick, m_bm);
            Poco::SharedPtr <UserModel> userM = Poco::makeShared<UserModel>(user);
            navigateWithUser(screens::START_USER_TAG, userM);
        }
        else {
            int id{};
            id = m_bm->getPerformerIdByLogin(login);
            id += m_bm->getUserIdByLogin(login);
            if (id != 0) {
                ui->l_error->setText(QString{"Пользователь с таким логином уже существует"});
                return;
            }
            id = m_bm->getPerformerIdByNickname(nick);
            id += m_bm->getUserIdByNickname(nick);
            if (id != 0) {
                ui->l_error->setText(QString{"Пользователь с таким никнеймом уже существует"});
                return;
            }

            m_bm->insertPerformer(login, nick, pass);
            Poco::SharedPtr <Performer> user = Poco::makeShared<Performer>(nick, m_bm);
            Poco::SharedPtr <PerformerModel> userM = Poco::makeShared<PerformerModel>(user);
            navigateWithUser(screens::START_PERF_TAG, userM);
        }
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.displayText();
    }
}


void RegistrFragment::on_pushButton_2_clicked() {
    backWithData(m_bm);
}

