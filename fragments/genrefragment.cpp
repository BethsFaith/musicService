#include "genrefragment.h"
#include "ui_genrefragment.h"

GenreFragment::GenreFragment(QWidget *parent) :
                                                BaseFragment(parent),
                                                ui(new Ui::GenreFragment)
{
  ui->setupUi(this);
  ui->pb_changeCover->setVisible(false);
  ui->pb_changeName->setVisible(false);
  ui->LE_name->setReadOnly(true);
}

GenreFragment::~GenreFragment()
{
  delete ui;
}

void GenreFragment::setData(Poco::SharedPtr<DBWorker> model)
{
  auto m = model;
  m_genre = m.unsafeCast<Genre>();
}

void GenreFragment::setUser(Poco::SharedPtr<BaseModel> model)
{
  m_user = model;
  auto user = m_user.cast<UserModel>();

  if (!user.isNull())
    if (user->m_userBase->isModerator())
    {
      ui->pb_changeCover->setVisible(true);
      ui->pb_changeName->setVisible(true);
      ui->LE_name->setReadOnly(false);
    }
}

void GenreFragment::update()
{
  if (!m_genre.isNull())
  {
    ui->LE_name->setText(m_genre->name().c_str());

    QPixmap picture(m_genre->cover_art().c_str());
    QSize PicSize(200, 200);

    picture = picture.scaled(PicSize,Qt::KeepAspectRatio);
    ui->l_Cover->resize(picture.height(), picture.width());
    ui->l_Cover->setPixmap(picture);

    QFrame *frame = new QFrame();
    QVBoxLayout *l = new QVBoxLayout(frame);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(frame);

    Poco::SharedPtr<UserModel> user;
    if (!m_user.isNull())
        user = m_user.cast<UserModel>();

    auto songs = m_genre->getSongs();
    for (int i{}; i < songs.size(); ++i)
    {
      m_songs.push_back(new SongPB());
      m_songs[i]->setName(songs[i].getName());
      m_songs[i]->setPerformer(songs[i].getPerformerName());
      m_songs[i]->id = songs[i].getId();
      connect(m_songs.at(i), &SongPB::clickedLike, this, &GenreFragment::on_like_clicked);
      connect(m_songs.at(i), &SongPB::clickedPerfomance, this, &GenreFragment::on_perf_clicked);
      connect(m_songs.at(i), &SongPB::clickedName, this, &GenreFragment::on_name_clicked);

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
      l->addWidget(m_songs[i]);
    }
  }
}

void GenreFragment::on_pb_changeCover_clicked()
{
  try{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg)"));
    if (!fileName.isEmpty())
    {
      m_genre->setCover_art(fileName.toStdString());
      QPixmap picture(fileName);
      QSize PicSize(200, 200);
      picture = picture.scaled(PicSize,Qt::KeepAspectRatio);
      ui->l_Cover->resize(picture.height(), picture.width());
      ui->l_Cover->setPixmap(picture);
    }
  }
  catch(Poco::Exception &ex)
  {
    std::cout << ex.displayText();
  }
}

void GenreFragment::on_like_clicked()
{
  auto user = m_user.cast<UserModel>();
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
//  update();
}

void GenreFragment::on_perf_clicked()
{
  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      Poco::SharedPtr<Performer> perf = Poco::makeShared<Performer>(button->getPerformer(), m_genre->getDB());
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

void GenreFragment::on_name_clicked()
{
  std::cout << "CLICKED" << std::endl;
  SongPB* button = qobject_cast<SongPB*>(sender());
  int id{};
  if( button != NULL )
  {
    std::cout << "!null" << std::endl;
    try{
      auto song = Poco::makeShared<Song>(button->id, m_genre->getDB());
      Poco::SharedPtr<Album> album = Poco::makeShared<Album>(song->getAlbumName(), song->getPerformerName(), m_genre->getDB());
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


void GenreFragment::on_pb_changeName_clicked()
{
  try{
    auto name = ui->LE_name->text();
    m_genre->setName(name.toStdString());
  }
  catch(Poco::Exception &ex)
  {
    std::cout << ex.displayText();
  }
}

