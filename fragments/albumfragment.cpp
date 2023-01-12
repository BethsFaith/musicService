#include "albumfragment.h"
#include "ui_albumfragment.h"

AlbumFragment::AlbumFragment(QWidget *parent) :
                                                BaseFragment(parent),
                                                ui(new Ui::AlbumFragment)
{
  ui->setupUi(this);

  ui->pb_public->setVisible(false);
  ui->pb_changeCover->setVisible(false);
  ui->pb_changeName->setVisible(false);
  ui->pb_remove->setVisible(false);
  ui->pb_addSong->setVisible(false);
  ui->LE_name->setReadOnly(true);
}

AlbumFragment::~AlbumFragment()
{
  delete ui;
}

void AlbumFragment::setData(Poco::SharedPtr<DBWorker> model)
{
  auto m = model;
  m_album = m.unsafeCast<Album>();

  ui->LE_name->setText( m_album->getName().c_str());
  ui->pb_perf->setText( m_album->getPerformerNickname().c_str());
  //  std::cout << m_playlist->getCoverArtRef() << "<- tut ref" << std::endl;
  QPixmap picture(m_album->getCoverArtRef().c_str());
  QSize PicSize(200, 200);
  picture = picture.scaled(PicSize,Qt::KeepAspectRatio);
  ui->l_Cover->resize(picture.height(), picture.width());
  ui->l_Cover->setPixmap(picture);
}

void AlbumFragment::setUser(Poco::SharedPtr<BaseModel> model)
{
  m_user = model;
}

void AlbumFragment::update()
{
  Poco::SharedPtr<UserModel> user;
  Poco::SharedPtr<PerformerModel> perf;
  if (!m_user.isNull())
  {
    perf = m_user.cast<PerformerModel>();
    user = m_user.cast<UserModel>();
  }

  QFrame *frame = new QFrame();
  QVBoxLayout *l = new QVBoxLayout(frame);
  ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->scrollArea->setWidgetResizable(true);
  ui->scrollArea->setWidget(frame);

  auto songs = m_album->getSongs();
  for (int i{}; i < songs.size(); ++i)
  {
    std::cout<< m_songs.size()<<" size of songs"<<std::endl;
    m_songs.push_back(new SongPB());
    m_songs[i]->setName(songs[i].getName());
    m_songs[i]->setPerformer(songs[i].getPerformerName());
    m_songs[i]->id = songs[i].getId();
    connect(m_songs.at(i), &SongPB::clickedName, this, &AlbumFragment::on_name_clicked);
    connect(m_songs.at(i), &SongPB::clickedPerfomance, this, &AlbumFragment::on_perf_clicked);
    connect(m_songs.at(i), &SongPB::clickedLike, this, &AlbumFragment::on_like_clicked);

    l->addWidget(m_songs[i]);

    if (!user.isNull())
    {
      auto addToPlaylist = new addSongToPlaylist("Добавить в плейлист");
      addToPlaylist->setUser(user);
      addToPlaylist->setIdSong(m_songs[i]->id);
      m_songs[i]->setActionToMenu(addToPlaylist);

      if (songs[i].isLiked(user->m_userBase->getLogin()))
        m_songs[i]->getLikeB()->setText("-");
      else
        std::cout << m_songs[i]->getName() << " isnt liked" << std::endl;
    }
    if (!perf.isNull())
      if (perf->getPerformer()->getName() == m_album->getPerformerNickname())
      {
        ui->pb_public->setVisible(true);
        ui->pb_changeCover->setVisible(true);
        ui->pb_changeName->setVisible(true);
        ui->pb_remove->setVisible(true);
        ui->pb_addSong->setVisible(true);
        ui->LE_name->setReadOnly(false);
        if (m_album->isPublic())
          ui->pb_public->setEnabled(false);
      }
  }
}

void AlbumFragment::on_like_clicked()
{
  auto user = m_user.cast<UserModel>();

  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    try{
      if (!user.isNull())
      {
        if (button->getLikeB()->text() == "+")
          user->m_userBase->rateSong(button->id, true);
        else
          user->m_userBase->rateSong(button->id, false);
        std::cout << "yes" << std::endl;
      }
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}

void AlbumFragment::on_name_clicked()
{

}

void AlbumFragment::on_perf_clicked()
{
  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      Poco::SharedPtr<Performer> perf = Poco::makeShared<Performer>(button->getPerformer(), m_album->getDB());
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

void AlbumFragment::on_pb_perf_clicked()
{
  try{
    Poco::SharedPtr<Performer> perf = Poco::makeShared<Performer>(m_album->getPerformerNickname(), m_album->getDB());
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

