#include "userfragment.h"
#include "ui_userfragment.h"

UserFragment::UserFragment(QWidget *parent) :
                                              BaseFragment(parent),
                                              ui(new Ui::UserFragment)
{
  ui->setupUi(this);
}

UserFragment::~UserFragment()
{
  delete ui;
}

void UserFragment::setUser(Poco::SharedPtr<BaseModel> model)
{
  m_ghostUser = model;
}

void UserFragment::setData(Poco::SharedPtr<DBWorker> model)
{
  m_mainUser = model.unsafeCast<User>();
}

void UserFragment::update()
{
  if (!m_mainUser.isNull())
  {
    ui->l_name->setText(m_mainUser->getNick().c_str());

    ui->scrollArea->setVisible(true);
    QFrame *frame = new QFrame();
    QVBoxLayout *l = new QVBoxLayout(frame);
    l->setDirection(QVBoxLayout::Direction::LeftToRight);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(frame);

    try {
      auto playlists = m_mainUser->getPlaylists();
      for (int i{}; i < playlists.size(); ++i)
      {
        m_playlists.push_back(new CategoryPB());
        m_playlists[i]->setName(playlists[i].getName());
        m_playlists[i]->setCreator(playlists[i].getUserNickname());
        QPixmap pixmap(QString{playlists[i].getCoverArtRef().c_str()});
        QIcon ButtonIcon(pixmap);
        m_playlists[i]->getPB()->setIcon(ButtonIcon);
        m_playlists[i]->getPB()->setIconSize(pixmap.rect().size());
        connect(m_playlists.at(i), &CategoryPB::clicked, this, &UserFragment::on_playlist_clicked);

        l->addWidget(m_playlists[i]);
      }
    }  catch (Poco::Exception &ex) {
      std::cout << ex.message();
    }
  }
}

void UserFragment::on_playlist_clicked()
{
  CategoryPB* button = qobject_cast<CategoryPB*>(sender());
  int id{};
  if( button != NULL )
  {
    try{
      id = m_mainUser->getDataBase()->getPlaylistId(button->getName(), button->getCreatorName());
      Poco::SharedPtr<Playlist> playlist = Poco::makeShared<Playlist>(id, m_mainUser->getDataBase());

      if (m_ghostUser.isNull())
        navigateWithData(screens::PLAYLIST_TAG, playlist);
      else
        navigateWithDataAndUser(screens::PLAYLIST_TAG, playlist, m_ghostUser);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}
