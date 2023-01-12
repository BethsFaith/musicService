#include "userfavourites.h"
#include "ui_userfavourites.h"
#include <QVBoxLayout>

UserFavourites::UserFavourites(QWidget *parent) :
                                                  BaseFragment(parent),
                                                  ui(new Ui::UserFavourites)
{
  ui->setupUi(this);
}

UserFavourites::~UserFavourites()
{
  delete ui;
}

void UserFavourites::setUser(Poco::SharedPtr<BaseModel> model)
{
  auto m = model;
  m_user = m.cast<UserModel>();

  std::cout << "USER FAV" << m_user << std::endl;
}

void UserFavourites::update()
{
  if (!m_user.isNull())
  {
    QFrame *frame = new QFrame();
    QVBoxLayout *l = new QVBoxLayout(frame);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(frame);

    auto songs = m_user->m_userBase->getUserLibrary()->getSongs();
    for (int i{}; i < songs.size(); ++i)
    {
      m_songs.push_back(new SongPB());
      m_songs[i]->setName(songs[i].getName());
      m_songs[i]->setPerformer(songs[i].getPerformerName());
      m_songs[i]->id = songs[i].getId();
      m_songs[i]->getLikeB()->setText("-");
      connect(m_songs.at(i), &SongPB::clickedName, this, &UserFavourites::on_name_clicked);
      connect(m_songs.at(i), &SongPB::clickedPerfomance, this, &UserFavourites::on_perf_clicked);
      connect(m_songs.at(i), &SongPB::clickedLike, this, &UserFavourites::on_like_clicked);

      auto addToPlaylist = new addSongToPlaylist("Добавить в плейлист");
      addToPlaylist->setUser(m_user);
      addToPlaylist->setIdSong(m_songs[i]->id);
      m_songs[i]->setActionToMenu(addToPlaylist);

      l->addWidget(m_songs[i]);
    }
  }
}

void UserFavourites::on_like_clicked()
{
  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    try{
       m_user->m_userBase->rateSong(button->id, false);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
  updateSongs();
}

void UserFavourites::on_name_clicked()
{
  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      auto song = Poco::makeShared<Song>(button->id, m_user->m_userBase->getDataBase());
      Poco::SharedPtr<Album> album = Poco::makeShared<Album>(song->getAlbumName(), song->getPerformerName(), m_user->m_userBase->getDataBase());
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

void UserFavourites::on_perf_clicked()
{
  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      //auto id = m_playlist->getDb()->getPerformerIdByNickname(button->getPerfomance());
      Poco::SharedPtr<Performer> perf = Poco::makeShared<Performer>(button->getPerformer(), m_user->m_userBase->getDataBase());
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

void UserFavourites::on_menu_clicked()
{
  //  connect(m_plForm, SIGNAL(playlistClicked(Poco::SharedPtr<Playlist>)()), this, SLOT(on_playlist_clicked(Poco::SharedPtr<Playlist>)));
}

void UserFavourites::updateSongs()
{
}

//void UserFavourites::on_playlist_clicked(Poco::SharedPtr<Playlist>)
//{

//}
