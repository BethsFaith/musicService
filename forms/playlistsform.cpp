#include "playlistsform.h"
#include "ui_playlistsform.h"

PlaylistsForm::PlaylistsForm(QWidget *parent) :
                                                QWidget(parent),
                                                ui(new Ui::PlaylistsForm)
{
  ui->setupUi(this);
}

PlaylistsForm::~PlaylistsForm()
{
  delete ui;
}

void PlaylistsForm::setUser(Poco::SharedPtr<UserModel> _user)
{
  m_user = _user;
}

void PlaylistsForm::setIdSong(int id)
{
  m_songId = id;
}
void PlaylistsForm::showWindow()
{
  ui->scrollArea->setVisible(true);
  QFrame *frame = new QFrame();
  QVBoxLayout *l = new QVBoxLayout(frame);
  ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setWidgetResizable(true);
  ui->scrollArea->setWidget(frame);

  try {
    auto playlists = m_user->m_userBase->getUserLibrary()->getOwnPlaylists();
    std::cout << playlists.size() << "- size" << std::endl;
    for (int i{}; i < playlists.size(); ++i)
    {
      m_playlists.push_back(new CategoryPB());
      m_playlists[i]->setName(playlists[i].getName());
      m_playlists[i]->setCreator(playlists[i].getUserNickname());
      QPixmap pixmap(QString{playlists[i].getCoverArtRef().c_str()});
      QSize PicSize(200, 200);
      pixmap = pixmap.scaled(PicSize,Qt::KeepAspectRatio);

      QIcon ButtonIcon(pixmap);
      m_playlists[i]->getPB()->setIcon(ButtonIcon);
      m_playlists[i]->getPB()->setIconSize(pixmap.rect().size());
      std::cout << playlists[i].getCoverArtRef() << "<- tut ref" << std::endl;
      connect(m_playlists.at(i), &CategoryPB::clicked, this, &PlaylistsForm::on_playlist_clicked);

      l->addWidget(m_playlists[i]);

      this->show();
    }
  }  catch (Poco::Exception &ex) {
    std::cout << ex.message();
  }
}

void PlaylistsForm::on_playlist_clicked()
{
  std::cout << "CLICKED" << std::endl;
  CategoryPB* button = qobject_cast<CategoryPB*>(sender());
  int id{};
  if( button != NULL )
  {
    try{
      std::cout << "!null" << std::endl;
      id = m_user->m_userBase->getDataBase()->getPlaylistId(button->getName(), button->getCreatorName());
      std::cout << std::to_string(id);
      Poco::SharedPtr<Playlist> playlist = Poco::makeShared<Playlist>(id, m_user->m_userBase->getDataBase());
      std::cout << std::to_string(playlist->getId());
      playlist->addSong(m_songId);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.displayText() << std::endl;
    }
  }
}
