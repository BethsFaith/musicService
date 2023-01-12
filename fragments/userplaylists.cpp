#include "userplaylists.h"
#include "ui_userplaylists.h"
#include <QVBoxLayout>

UserPlaylists::UserPlaylists(QWidget *parent) :
                                                BaseFragment(parent),
                                                ui(new Ui::UserPlaylists)
{
  ui->setupUi(this);
}

UserPlaylists::~UserPlaylists()
{
  delete ui;
}

void UserPlaylists::setUser(Poco::SharedPtr<BaseModel> model)
{
  m_user = model.cast<UserModel>();
}

void UserPlaylists::update()
{
  if (!m_user.isNull())
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

      for (int i{}; i < playlists.size(); ++i)
      {
        m_playlists.push_back(new CategoryPB());
        m_playlists[i]->setName(playlists[i].getName());
        m_playlists[i]->setCreator(playlists[i].getUserNickname());

        QPixmap pixmap(QString{playlists[i].getCoverArtRef().c_str()});
        pixmap = pixmap.scaled(200, 200);
        QIcon ButtonIcon(pixmap);
        m_playlists[i]->getPB()->setIcon(ButtonIcon);
        m_playlists[i]->getPB()->setIconSize(pixmap.rect().size());

        connect(m_playlists.at(i), &CategoryPB::clicked, this, &UserPlaylists::on_pushButton_clicked);

        l->addWidget(m_playlists[i]);
      }
    }  catch (Poco::Exception &ex) {
      std::cout << ex.message();
    }
  }
}

void UserPlaylists::on_pushButton_clicked()
{
  std::cout << "CLICKED" << std::endl;
  CategoryPB* button = qobject_cast<CategoryPB*>(sender());
  int id{};
  if( button != NULL )
  {
    try{
      id = m_user->m_userBase->getDataBase()->getPlaylistId(button->getName(), button->getCreatorName());

      Poco::SharedPtr<Playlist> playlist = Poco::makeShared<Playlist>(id, m_user->m_userBase->getDataBase());
      std::cout << playlist->getCoverArtRef() << "<- tut ref" << std::endl;

      navigateWithDataAndUser(screens::PLAYLIST_TAG, playlist, m_user);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}


void UserPlaylists::on_pb_create_clicked()
{
    navigateWithUser(screens::CREATE_PLAYLIST_TAG, m_user);
}

