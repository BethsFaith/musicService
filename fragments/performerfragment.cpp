#include "performerfragment.h"
#include "ui_performerfragment.h"

PerformerFragment::PerformerFragment(QWidget *parent) :
                                                        BaseFragment(parent),
                                                        ui(new Ui::PerformerFragment)
{
  ui->setupUi(this);
}

PerformerFragment::~PerformerFragment()
{
  delete ui;
}

void PerformerFragment::setUser(Poco::SharedPtr<BaseModel> model)
{
  m_user = model;
}

void PerformerFragment::setData(Poco::SharedPtr<DBWorker> model)
{
  m_performer = model.unsafeCast<Performer>();
}

void PerformerFragment::update()
{
  if (!m_performer.isNull())
  {
    ui->l_name->setText(m_performer->getName().c_str());

    ui->SA_albums->setVisible(true);
    QFrame *frame = new QFrame();
    QVBoxLayout *l = new QVBoxLayout(frame);
    l->setDirection(QVBoxLayout::Direction::LeftToRight);
    ui->SA_albums->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->SA_albums->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->SA_albums->setWidgetResizable(true);
    ui->SA_albums->setWidget(frame);

    try {
      auto albums = m_performer->getAlbums();
      for (int i{}; i < albums.size(); ++i)
      {
        m_albums.push_back(new CategoryPB());
        m_albums[i]->setName(albums[i].getName());
        m_albums[i]->setCreator(albums[i].getPerformerNickname());
        QPixmap pixmap(QString{albums[i].getCoverArtRef().c_str()});
        QIcon ButtonIcon(pixmap);
        m_albums[i]->getPB()->setIcon(ButtonIcon);
        m_albums[i]->getPB()->setIconSize(pixmap.rect().size());
        std::cout << albums[i].getCoverArtRef() << "<- tut ref" << std::endl;
        connect(m_albums.at(i), &CategoryPB::clicked, this, &PerformerFragment::on_album_clicked);

        l->addWidget(m_albums[i]);
      }
    }  catch (Poco::Exception &ex) {
      std::cout << ex.message();
    }

    ui->SA_Songs->setVisible(true);
    QFrame *frame2 = new QFrame();
    QVBoxLayout *l2 = new QVBoxLayout(frame2);
    ui->SA_Songs->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->SA_Songs->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->SA_Songs->setWidgetResizable(true);
    ui->SA_Songs->setWidget(frame2);

    Poco::SharedPtr<UserModel> user;
    if (!m_user.isNull())
      user = m_user.cast<UserModel>();

    try {
      auto songs = m_performer->getSongs();
      for (int i{}; i < songs.size(); ++i)
      {
        m_songs.push_back(new SongPB());
        m_songs[i]->setName(songs[i].getName());
        m_songs[i]->setPerformer(songs[i].getPerformerName());
        m_songs[i]->id = songs[i].getId();
        connect(m_songs.at(i), &SongPB::clickedName, this, &PerformerFragment::on_name_clicked);
        connect(m_songs.at(i), &SongPB::clickedPerfomance, this, &PerformerFragment::on_perf_clicked);
        connect(m_songs.at(i), &SongPB::clickedLike, this, &PerformerFragment::on_like_clicked);

        if (!user.isNull())
        {
          auto addToPlaylist = new addSongToPlaylist("Добавить в плейлист");
          addToPlaylist->setUser(user);
          addToPlaylist->setIdSong(m_songs[i]->id);
          m_songs[i]->setActionToMenu(addToPlaylist);

          if (songs[i].isLiked(user->m_userBase->getLogin()))
            m_songs[i]->getLikeB()->setText("-");
          else
            std::cout << songs[i].getName() << " isnt liked" << std::endl;
        }
        l2->addWidget(m_songs[i]);
      }
    }  catch (Poco::Exception &ex) {
      std::cout << ex.message();
    }
  }
}

void PerformerFragment::on_album_clicked()
{
  CategoryPB* button = qobject_cast<CategoryPB*>(sender());
  int id{};
  if( button != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      Poco::SharedPtr<Album> album = Poco::makeShared<Album>(button->getName(), m_performer->getName(), m_performer->dataBase());
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

void PerformerFragment::on_like_clicked()
{
  auto user = m_user.unsafeCast<UserModel>();
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

void PerformerFragment::on_name_clicked()
{
  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    try{
      auto song = Poco::makeShared<Song>(button->id, m_performer->dataBase());
      Poco::SharedPtr<Album> album = Poco::makeShared<Album>(song->getAlbumName(), m_performer->getName(), m_performer->dataBase());
      if (m_user.isNull())
        navigateWithData(screens::ALBUM_TAG, album);
      else
        navigateWithDataAndUser(screens::ALBUM_TAG, album, m_user);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.displayText() << std::endl;
    }
  }
}

void PerformerFragment::on_perf_clicked()
{

}
