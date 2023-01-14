#include "searchfragment.h"
#include "ui_searchfragment.h"

SearchFragment::SearchFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::SearchFragment) {
    ui->setupUi(this);
    m_groupBox = new QButtonGroup();
    m_groupBox->addButton(ui->RB_Songs);
    m_groupBox->addButton(ui->RB_Albums);
    m_groupBox->addButton(ui->RB_Users);
    m_groupBox->addButton(ui->RB_Playlists);
    m_groupBox->addButton(ui->RB_Perf);

    m_groupBox->setId(ui->RB_Songs, ButtonsId::SONGS);
    m_groupBox->setId(ui->RB_Albums, ButtonsId::ALBUMS);
    m_groupBox->setId(ui->RB_Perf, ButtonsId::PERFORMERS);
    m_groupBox->setId(ui->RB_Users, ButtonsId::USERS);
    m_groupBox->setId(ui->RB_Playlists, ButtonsId::PLAYLISTS);

    ui->RB_Songs->setChecked(true);

    for (const auto b: m_groupBox->buttons())
        connect(b, &QPushButton::clicked, this, &SearchFragment::on_LE_browser_editingFinished);

    m_frame = new QFrame();
    m_layout = new QVBoxLayout(m_frame);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(m_frame);
}

SearchFragment::~SearchFragment() {
    delete ui;
}

void SearchFragment::setData(Poco::SharedPtr <DBWorker> model) {
    auto db = model.cast<DataBase>();
    m_sharedLib = Poco::makeShared<SharedLibrary>(db);
    std::cout << m_sharedLib << std::endl;
}

void SearchFragment::setUser(Poco::SharedPtr <BaseModel> model) {
    m_baseM = model;
    m_user = model.cast<UserModel>();

    if (m_sharedLib.isNull()) {
        if (!m_user.isNull())
            m_sharedLib = Poco::makeShared<SharedLibrary>(m_user->m_userBase->getDataBase());
        else {
            auto perf = model.cast<PerformerModel>();
            m_sharedLib = Poco::makeShared<SharedLibrary>(perf->getPerformer()->dataBase());
        }
    }
}

void SearchFragment::update() {
    int id = m_groupBox->checkedId();
    switch (id) {
        case (ButtonsId::USERS) :
            updateUsers();
            break;
        case (ButtonsId::PERFORMERS) :
            updatePerformers();
            break;
        case (ButtonsId::SONGS) :
            updateSongs();
            break;
        case (ButtonsId::ALBUMS) :
            updateAlbums();
            break;
        case (ButtonsId::PLAYLISTS) :
            updatePlaylists();
            break;
    }
}

void SearchFragment::on_LE_browser_editingFinished() {
    for (int i = m_searchableButtons.size() - 1; i >= 0; --i) {
        m_layout->removeWidget(m_searchableButtons[i]);
        m_searchableButtons[i]->hide();
        //delete m_searchableButtons[i];
        m_searchableButtons.erase(--m_searchableButtons.end());
    }
    this->update();
}

void SearchFragment::updateSongs() {
    try {
        m_songs.clear();
        auto songs = m_sharedLib->getAllSongs();
        for (int i{}; i < songs.size(); ++i) {
            std::cout << ui->LE_browser->text().toStdString() << std::endl;
            if (!ui->LE_browser->text().isEmpty()) {
                bool f{false};
                size_t pos = songs[i].getName().find(ui->LE_browser->text().toStdString());
                if (pos != std::string::npos)
                    f = true;
                pos = songs[i].getPerformerName().find(ui->LE_browser->text().toStdString());
                if (pos != std::string::npos)
                    f = true;

                if (!f)
                    continue;
            }
            auto s = new SongPB(songs[i], this, m_user);

            if (!m_user.isNull()) {
                auto addToPlaylist = new addSongToPlaylist("Добавить в плейлист");
                addToPlaylist->setUser(m_user);
                addToPlaylist->setIdSong(songs[i].getId());
                s->setActionToMenu(addToPlaylist);
            }
            m_layout->addWidget(s);
            m_searchableButtons.push_back(s);
        }
    }
    catch (Poco::Exception &ex) {
        std::cout << ex.displayText();
    }
    catch (std::exception &ex) {
        std::cout << ex.what();
    }
}

void SearchFragment::updatePerformers() {
    auto performers = m_sharedLib->getAllPerformers();
    for (auto &performer: performers) {
        if (!ui->LE_browser->text().isEmpty()) {
            std::cout << ui->LE_browser->text().toStdString() << std::endl;
            size_t pos = performer.getName().find(ui->LE_browser->text().toStdString());
            if (pos == std::string::npos)
                continue;
        }
        auto pb = new QPushButton;
        pb->setText(performer.getName().c_str());
        pb->setFixedSize(650, 74);
        pb->setMinimumSize(650, 74);
        pb->setMaximumSize(650, 74);
        connect(pb, &QPushButton::clicked, this, &SearchFragment::clickedPerformer);
        m_layout->addWidget(pb);
        m_searchableButtons.push_back(pb);
    }
}

void SearchFragment::clickedPerformer() {
    auto btn = qobject_cast<QPushButton *>(sender());
    if (btn != NULL) {
        std::cout << "!null" << std::endl;
        try {
            Poco::SharedPtr <Performer> perf = Poco::makeShared<Performer>(btn->text().toStdString(),
                                                                           m_sharedLib->dataBase());
            if (m_baseM.isNull())
                navigateWithData(screens::PERFORMER_TAG, perf);
            else
                navigateWithDataAndUser(screens::PERFORMER_TAG, perf, m_baseM);
        }
        catch (Poco::Exception &ex) {
            std::cout << ex.message() << std::endl;
        }
    }
}

void SearchFragment::updateAlbums() {
    try {
        auto albums = m_sharedLib->getAllAlbums();
        for (int i{}; i < albums.size(); ++i) {
            if (!ui->LE_browser->text().isEmpty()) {
                std::cout << ui->LE_browser->text().toStdString() << std::endl;
                bool f{false};
                size_t pos = albums[i].getName().find(ui->LE_browser->text().toStdString());
                if (pos != std::string::npos)
                    f = true;
                pos = albums[i].getPerformerNickname().find(ui->LE_browser->text().toStdString());
                if (pos != std::string::npos)
                    f = true;

                if (!f)
                    continue;
            }
            auto albumPB = new AlbumPB(albums[i], this, m_user);

            m_layout->addWidget(albumPB);
            m_searchableButtons.push_back(albumPB);
        }
    } catch (Poco::Exception &ex) {
        std::cout << ex.message();
    }
}

void SearchFragment::updatePlaylists() {
    try {
        auto playlists = m_sharedLib->getAllPlaylists();
        for (int i{}; i < playlists.size(); ++i) {
            if (!ui->LE_browser->text().isEmpty()) {
                std::cout << ui->LE_browser->text().toStdString() << std::endl;
                bool f{false};
                size_t pos = playlists[i].getName().find(ui->LE_browser->text().toStdString());
                if (pos != std::string::npos)
                    f = true;
                pos = playlists[i].getUserNickname().find(ui->LE_browser->text().toStdString());
                if (pos != std::string::npos)
                    f = true;
                if (!f)
                    continue;
            }
            auto playlistPB = new PlaylistPB(playlists[i], this, m_user);

            m_layout->addWidget(playlistPB);
            m_searchableButtons.push_back(playlistPB);
        }
    } catch (Poco::Exception &ex) {
        std::cerr << ex.displayText();
    }
}

void SearchFragment::updateUsers() {
    auto users = m_sharedLib->getAllUsers();
    for (auto &user: users) {
        if (!ui->LE_browser->text().isEmpty()) {
            std::cout << ui->LE_browser->text().toStdString() << std::endl;
            size_t pos = user.getNick().find(ui->LE_browser->text().toStdString());
            if (pos == std::string::npos)
                continue;
        }
        auto pb = new QPushButton;
        pb->setText(user.getNick().c_str());
        pb->setFixedSize(650, 74);
        connect(pb, &QPushButton::clicked, this, &SearchFragment::clickedUser);
        m_layout->addWidget(pb);
        m_searchableButtons.push_back(pb);
    }
}

void SearchFragment::clickedUser() {
    auto btn = qobject_cast<QPushButton *>(sender());
    if (btn != NULL) {
        try {
            auto user = Poco::makeShared<User>(btn->text().toStdString(), m_sharedLib->dataBase());

            if (m_baseM.isNull())
                navigateWithData(screens::USER_TAG, user);
            else
                navigateWithDataAndUser(screens::USER_TAG, user, m_baseM);
        }
        catch (Poco::Exception &ex) {
            std::cerr << ex.displayText();
        }
    }
}
