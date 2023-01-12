#include "searchfragment.h"
#include "ui_searchfragment.h"

SearchFragment::SearchFragment(QWidget *parent) :
                                                  BaseFragment(parent),
                                                  ui(new Ui::SearchFragment)
{
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

  for (const auto b : m_groupBox->buttons())
    connect(b, &QPushButton::clicked, this, &SearchFragment::update);
}

SearchFragment::~SearchFragment()
{
  delete ui;
  delete m_groupBox;
}

void SearchFragment::setData(Poco::SharedPtr<DBWorker> model)
{
  std::cout << "DATA FOR SEARCH" << std::endl;
  auto db = model.unsafeCast<DataBase>();
  m_sharedLib = Poco::makeShared<SharedLibrary>(db);
  std::cout << m_sharedLib;
}

void SearchFragment::setUser(Poco::SharedPtr<BaseModel> model)
{
  m_baseM = model;
  m_user = model.cast<UserModel>();

  if (m_sharedLib.isNull())
  {
    if (!m_user.isNull())
      m_sharedLib = Poco::makeShared<SharedLibrary>(m_user->m_userBase->getDataBase());
    else
    {
      auto perf = model.cast<PerformerModel>();
      m_sharedLib = Poco::makeShared<SharedLibrary>(perf->getPerformer()->dataBase());
    }
  }
}

void SearchFragment::update()
{
  int id = m_groupBox->checkedId();
  std::cout << id << ":id" << std::endl;
  switch(id)
  {
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

void SearchFragment::on_LE_browser_editingFinished()
{
//  if (m_frame != nullptr)
//    delete m_frame;
//  if (m_layout != nullptr)
//    delete m_layout;

  this->update();
}

void SearchFragment::updateSongs()
{
  m_frame = new QFrame();
  m_layout = new QVBoxLayout(m_frame);
  ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->scrollArea->setWidgetResizable(true);
  ui->scrollArea->setWidget(m_frame);

//  for (auto song : m_songs)
//    delete song;
  try{
    m_songs.clear();

    auto songs = m_sharedLib->getAllSongs();
    for (int i{}; i < songs.size(); ++i)
    {
      if (!ui->LE_browser->text().isEmpty())
      {
        std::cout << ui->LE_browser->text().toStdString() << std::endl;
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
      QPointer<SongPB> s = new SongPB();

      s->setName(songs[i].getName());
      s->setPerformer(songs[i].getPerformerName());
      s->id = songs[i].getId();
      connect(s, &SongPB::clickedName, this, &SearchFragment::on_song_name_clicked);
      connect(s, &SongPB::clickedPerfomance, this, &SearchFragment::on_song_perf_clicked);
      connect(s, &SongPB::clickedLike, this,&SearchFragment::on_song_like_clicked);

      m_layout->addWidget(s);

      if (!m_user.isNull())
      {
        auto addToPlaylist = new addSongToPlaylist("Добавить в плейлист");
        addToPlaylist->setUser(m_user);
        addToPlaylist->setIdSong(songs[i].getId());
        s->setActionToMenu(addToPlaylist);

        if (songs[i].isLiked(m_user->m_userBase->getLogin()))
          s->getLikeB()->setText("-");
        else
          std::cout << s->getName() << " isnt liked" << std::endl;
      }
    }
  }
  catch(Poco::Exception &ex)
  {
    std::cout << ex.displayText();
  }
  catch(std::exception &ex)
  {
    std::cout << ex.what();
  }
}

void SearchFragment::on_song_like_clicked()
{
  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    try{
      if (!m_user.isNull())
      {
        if (button->getLikeB()->text() == "+")
          m_user->m_userBase->rateSong(button->id, true);
        else
          m_user->m_userBase->rateSong(button->id, false);
        std::cout << "yes" << std::endl;
      }
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}

void SearchFragment::on_song_name_clicked()
{
  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      auto song = Poco::makeShared<Song>(button->id, m_sharedLib->dataBase());
      Poco::SharedPtr<Album> album = Poco::makeShared<Album>(song->getAlbumName(), song->getPerformerName(), m_sharedLib->dataBase());
      std::cout << album << ":album" << std::endl;
      if (m_baseM.isNull())
        navigateWithData(screens::ALBUM_TAG, album);
      else
        navigateWithDataAndUser(screens::ALBUM_TAG, album, m_baseM);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}

void SearchFragment::on_song_perf_clicked()
{
  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  if( button != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      Poco::SharedPtr<Performer> perf = Poco::makeShared<Performer>(button->getPerformer(), m_sharedLib->dataBase());
      std::cout << perf << ":perf" << std::endl;
      if (m_baseM.isNull())
        navigateWithData(screens::PERFORMER_TAG, perf);
      else
        navigateWithDataAndUser(screens::PERFORMER_TAG, perf, m_baseM);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}


void SearchFragment::updatePerformers()
{
  m_frame = new QFrame();
  m_layout = new QVBoxLayout(m_frame);
  ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->scrollArea->setWidgetResizable(true);
  ui->scrollArea->setWidget(m_frame);

  auto performers = m_sharedLib->getAllPerformers();
  for (auto &performer : performers)
  {
    if (!ui->LE_browser->text().isEmpty())
    {
      std::cout << ui->LE_browser->text().toStdString() << std::endl;
      size_t pos = performer.getName().find(ui->LE_browser->text().toStdString());
      if (pos == std::string::npos)
        continue;
    }
    QPointer<QPushButton> pb = new QPushButton;
    pb->setText(performer.getName().c_str());
    pb->setFixedSize(650, 74);
//    pb.setFont(QFont());
    pb->setMinimumSize(650, 74);
    pb->setMaximumSize(650, 74);
    connect(pb, &QPushButton::clicked, this, &SearchFragment::clickedPerformer);
    m_layout->addWidget(pb);
  }
}

void SearchFragment::clickedPerformer()
{
  std::cout << "CLICKED" << std::endl;
  auto btn = qobject_cast<QPushButton*>(sender());
  if( btn != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      Poco::SharedPtr<Performer> perf = Poco::makeShared<Performer>(btn->text().toStdString(), m_sharedLib->dataBase());
      std::cout << perf << ":perf" << std::endl;
      if (m_baseM.isNull())
        navigateWithData(screens::PERFORMER_TAG, perf);
      else
        navigateWithDataAndUser(screens::PERFORMER_TAG, perf, m_baseM);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}

void SearchFragment::updateAlbums()
{
  std::cout << "ALBUMS" << std::endl;
  m_frame = new QFrame();
  m_layout = new QVBoxLayout(m_frame);
  ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->scrollArea->setWidgetResizable(true);
  ui->scrollArea->setWidget(m_frame);

  try {
    auto albums = m_sharedLib->getAllAlbums();
    for (int i{}; i < albums.size(); ++i)
    {
      if (!ui->LE_browser->text().isEmpty())
      {
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
      QPointer<CategoryPB> albumPB = new CategoryPB;
      albumPB->setName(albums[i].getName());
      albumPB->setCreator(albums[i].getPerformerNickname());
      QPixmap pixmap(QString{albums[i].getCoverArtRef().c_str()});
      QIcon ButtonIcon(pixmap);
      albumPB->getPB()->setIcon(ButtonIcon);
      albumPB->getPB()->setIconSize(pixmap.rect().size());
      std::cout << albums[i].getCoverArtRef() << "<- tut ref" << std::endl;
      connect(albumPB, &CategoryPB::clicked, this, &SearchFragment::clickedAlbum);

      m_layout->addWidget(albumPB);
    }
  }  catch (Poco::Exception &ex) {
    std::cout << ex.message();
  }
}

void SearchFragment::clickedAlbum()
{
  std::cout << "CLICKED" << std::endl;
  auto btn = qobject_cast<CategoryPB*>(sender());
  if( btn != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      Poco::SharedPtr<Album> album = Poco::makeShared<Album>(btn->getName(), btn->getCreatorName(), m_sharedLib->dataBase());
      std::cout << album << ":perf" << std::endl;
      if (m_baseM.isNull())
        navigateWithData(screens::ALBUM_TAG, album);
      else
        navigateWithDataAndUser(screens::ALBUM_TAG, album, m_baseM);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}

void SearchFragment::updatePlaylists()
{
  m_frame = new QFrame();
  m_layout = new QVBoxLayout(m_frame);
  ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->scrollArea->setWidgetResizable(true);
  ui->scrollArea->setWidget(m_frame);

  try {
    auto playlists = m_sharedLib->getAllPlaylists();
    for (int i{}; i < playlists.size(); ++i)
    {
      if (!ui->LE_browser->text().isEmpty())
      {
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
      QPointer<CategoryPB> playlistPB = new CategoryPB;
      playlistPB->setName(playlists[i].getName());
      playlistPB->setCreator(playlists[i].getUserNickname());
      QPixmap pixmap(QString{playlists[i].getCoverArtRef().c_str()});
      QIcon ButtonIcon(pixmap);
      playlistPB->getPB()->setIcon(ButtonIcon);
      playlistPB->getPB()->setIconSize(pixmap.rect().size());
      std::cout << playlists[i].getCoverArtRef() << "<- tut ref" << std::endl;
      connect(playlistPB, &CategoryPB::clicked, this, &SearchFragment::clickedPlaylist);

      m_layout->addWidget(playlistPB);
    }
  }  catch (Poco::Exception &ex) {
    std::cout << ex.message();
  }
}

void SearchFragment::clickedPlaylist()
{
  std::cout << "CLICKED" << std::endl;
  auto btn = qobject_cast<CategoryPB*>(sender());
  if( btn != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      Poco::SharedPtr<Playlist> playlist = Poco::makeShared<Playlist>(btn->getCreatorName(), btn->getName(), m_sharedLib->dataBase());
      std::cout << playlist << ":playlist" << std::endl;
      if (m_baseM.isNull())
        navigateWithData(screens::PLAYLIST_TAG, playlist);
      else
        navigateWithDataAndUser(screens::PLAYLIST_TAG, playlist, m_baseM);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}

void SearchFragment::updateUsers()
{
  m_frame = new QFrame();
  m_layout = new QVBoxLayout(m_frame);
  ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->scrollArea->setWidgetResizable(true);
  ui->scrollArea->setWidget(m_frame);

  auto users = m_sharedLib->getAllUsers();
  for (auto &user : users)
  {
    if (!ui->LE_browser->text().isEmpty())
    {
      std::cout << ui->LE_browser->text().toStdString() << std::endl;
      size_t pos = user.getNick().find(ui->LE_browser->text().toStdString());
      if (pos == std::string::npos)
        continue;
    }
    QPointer<QPushButton> pb = new QPushButton;
    pb->setText(user.getNick().c_str());
    pb->setFixedSize(650, 74);
    connect(pb, &QPushButton::clicked, this, &SearchFragment::clickedUser);
    m_layout->addWidget(pb);
  }
}

void SearchFragment::clickedUser()
{
  std::cout << "CLICKED" << std::endl;
  auto btn = qobject_cast<QPushButton*>(sender());
  if( btn != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      Poco::SharedPtr<User> user = Poco::makeShared<User>(btn->text().toStdString(), m_sharedLib->dataBase());

      if (m_baseM.isNull())
        navigateWithData(screens::USER_TAG, user);
      else
        navigateWithDataAndUser(screens::USER_TAG, user, m_baseM);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}
