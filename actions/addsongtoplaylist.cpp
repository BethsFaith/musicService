#include "addsongtoplaylist.h"

addSongToPlaylist::addSongToPlaylist(QString text, QObject *parent) : QAction(text, parent)
{
  connect(this, &QAction::triggered, this, &addSongToPlaylist::action);
}

addSongToPlaylist::~addSongToPlaylist()
{

}

Poco::SharedPtr<UserModel> addSongToPlaylist::user()
{
  return m_user;
}

void addSongToPlaylist::setUser(Poco::SharedPtr<UserModel> newUser)
{
  std::cout << "newUser!" << newUser;
  m_user = newUser;
}

int addSongToPlaylist::idSong()
{
  return m_idSong;
}

void addSongToPlaylist::setIdSong(int newIdSong)
{
  std::cout << "newSong!" << newIdSong;
  m_idSong = newIdSong;
}

void addSongToPlaylist::action()
{
  std::cout << "ADD ACTION" << std::endl;
  m_plForm = Poco::makeShared<PlaylistsForm>();
  m_plForm->setUser(m_user);
  m_plForm->setIdSong(m_idSong);
  m_plForm->showWindow();
}
