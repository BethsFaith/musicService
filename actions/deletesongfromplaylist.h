#ifndef DELETESONGFROMPLAYLIST_H
#define DELETESONGFROMPLAYLIST_H

#include <QAction>
#include "../models/usermodel.h"
#include "../forms/playlistsform.h"


class deleteSongFromPlaylist : public QAction
{
public:
  explicit deleteSongFromPlaylist(QString string, QObject *parent = nullptr);
  virtual ~deleteSongFromPlaylist();


  Poco::SharedPtr<Playlist> playlist();
  void setPlaylist(Poco::SharedPtr<Playlist> newPlaylist);

  int idSong();
  void setIdSong(int newIdSong);

public slots:
  void action();

private:
  Poco::SharedPtr<Playlist> m_playlist;
  int m_idSong;
  Poco::SharedPtr<PlaylistsForm> m_plForm;
};

#endif // DELETESONGFROMPLAYLIST_H
