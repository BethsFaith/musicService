#include "playlistfragment.h"
#include "ui_playlistfragment.h"

PlaylistFragment::PlaylistFragment(QWidget *parent) :
                                                      BaseFragment(parent),
                                                      ui(new Ui::PlaylistFragment)
{
  ui->setupUi(this);
  ui->RB_Public->setVisible(false);
  ui->pb_changeCover->setVisible(false);
  ui->pb_remove->setVisible(false);
  ui->pb_changeName->setVisible(false);
  ui->LE_name->setReadOnly(true);
}

PlaylistFragment::~PlaylistFragment()
{
  delete ui;
}

void PlaylistFragment::setData(Poco::SharedPtr<DBWorker> model)
{
  auto m = model;
  m_playlist = m.unsafeCast<Playlist>();

  ui->LE_name->setText(m_playlist->getName().c_str());
  ui->pb_user->setText(m_playlist->getUserNickname().c_str());
  QPixmap picture(m_playlist->getCoverArtRef().c_str());
  QSize PicSize(290, 290);
  picture = picture.scaled(PicSize,Qt::KeepAspectRatio);
 // ui->l_Cover->resize(picture.height(), picture.width());
  ui->l_Cover->setPixmap(picture);
}

void PlaylistFragment::setUser(Poco::SharedPtr<BaseModel> model)
{
  m_user = model;
}

void PlaylistFragment::update()
{
  try
  {
    Poco::SharedPtr<UserModel> user;
    if (!m_user.isNull())
    {
      user = m_user.cast<UserModel>();
      if (!user.isNull())
        if (m_playlist->getUserNickname() == user->m_userBase->getNick())
        {
          ui->RB_Public->setVisible(true);
          ui->pb_changeCover->setVisible(true);
          ui->pb_changeName->setVisible(true);
          ui->pb_remove->setVisible(true);
          ui->LE_name->setReadOnly(false);
          ui->RB_Public->setChecked(m_playlist->isPublic());
        }
    }

    QFrame *frame = new QFrame();
    QVBoxLayout *l = new QVBoxLayout(frame);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(frame);

    auto songs = m_playlist->getSongs();
    for (int i{}; i < songs.size(); ++i)
    {
      std::cout<< m_songs.size()<<" size of songs"<<std::endl;
      m_songs.push_back(new SongPB());
      m_songs[i]->setName(songs[i].getName());
      m_songs[i]->setPerformer(songs[i].getPerformerName());
      m_songs[i]->id = songs[i].getId();
      connect(m_songs.at(i), &SongPB::clickedName, this, &PlaylistFragment::on_name_clicked);
      connect(m_songs.at(i), &SongPB::clickedPerfomance, this, &PlaylistFragment::on_perf_clicked);
      connect(m_songs.at(i), &SongPB::clickedLike, this, &PlaylistFragment::on_like_clicked);

      l->addWidget(m_songs[i]);

      if (!user.isNull())
      {
        if (m_playlist->getUserNickname() == user->m_userBase->getNick())
        {
          std::cout << "VIS" << std::endl;

          auto remove = new deleteSongFromPlaylist("Удалить из плейлиста");
          remove->setPlaylist(m_playlist);
          remove->setIdSong(m_songs[i]->id);
          m_songs[i]->clearMenu();
          m_songs[i]->setActionToMenu(remove);
        }
        else
        {
          auto addToPlaylist = new addSongToPlaylist("Добавить в плейлист");
          addToPlaylist->setUser(user);
          addToPlaylist->setIdSong(m_songs[i]->id);
          m_songs[i]->setActionToMenu(addToPlaylist);
        }

        if (songs[i].isLiked(user->m_userBase->getLogin()))
          m_songs[i]->getLikeB()->setText("-");
        else
          std::cout << m_songs[i]->getName() << " isnt liked" << std::endl;
      }
    }
  }
  catch(Poco::Exception &ex)
  {
    std::cout << ex.displayText() << std::endl;
    std::cout << ex.message() << std::endl;;
  }
}

void PlaylistFragment::on_like_clicked()
{
  Poco::SharedPtr<UserModel> user;
  if (!m_user.isNull())
    user = m_user.unsafeCast<UserModel>();
  if (user.isNull())
    return;

  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    try{
      if (button->getLikeB()->text() == "+")
        user->m_userBase->rateSong(button->id, true);
      else
        user->m_userBase->rateSong(button->id, false);
      std::cout << "yes" << std::endl;
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}

void PlaylistFragment::on_name_clicked()
{
  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    try{
      auto song = Poco::makeShared<Song>(button->id, m_playlist->getDb());
      Poco::SharedPtr<Album> album = Poco::makeShared<Album>(song->getAlbumName(), song->getPerformerName(), m_playlist->getDb());
      std::cout << album << ":album" << std::endl;
      if (m_user.isNull())
        navigateWithData(screens::ALBUM_TAG, album);
      else
        navigateWithDataAndUser(screens::ALBUM_TAG, album, m_user);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}

void PlaylistFragment::on_perf_clicked()
{
  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      Poco::SharedPtr<Performer> perf = Poco::makeShared<Performer>(button->getPerformer(), m_playlist->getDb());
      std::cout << perf << ":perf" << std::endl;
      if (m_user.isNull())
        navigateWithData(screens::PERFORMER_TAG, perf);
      else
        navigateWithDataAndUser(screens::PERFORMER_TAG, perf, m_user);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}

void PlaylistFragment::on_pb_changeName_clicked()
{
  try{
    auto name = ui->LE_name->text();
    m_playlist->setName(name.toStdString());
  }
  catch(Poco::Exception &ex)
  {
    std::cout << ex.displayText();
  }
}


void PlaylistFragment::on_pb_remove_clicked()
{
  m_playlist->getDb()->deletePlaylist(m_playlist->getId());
  backWithUser(m_user);
}

void PlaylistFragment::on_pb_changeCover_clicked()
{
  try{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg)"));
    if (!fileName.isEmpty())
    {
      m_playlist->setCoverArt(fileName.toStdString());
      QPixmap picture(fileName);
      QSize PicSize(200, 200);
      picture = picture.scaled(PicSize,Qt::KeepAspectRatio);
//      ui->l_Cover->resize(picture.height(), picture.width());
      ui->l_Cover->setPixmap(picture);
    }
  }
  catch(Poco::Exception &ex)
  {
    std::cout << ex.displayText();
  }
}


void PlaylistFragment::on_RB_Public_clicked(bool checked)
{
  m_playlist->setPublic(checked);
}


void PlaylistFragment::on_pb_user_clicked()
{
  try{
    Poco::SharedPtr<User> user = Poco::makeShared<User>(m_playlist->getUserNickname(), m_playlist->getDb());
    if (m_user.isNull())
      navigateWithData(screens::USER_TAG, user);
    else
      navigateWithDataAndUser(screens::USER_TAG, user, m_user);
  }
  catch(Poco::Exception &ex)
  {
    std::cout << ex.message() << std::endl;
  }
}

