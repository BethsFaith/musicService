#include "playlistmodel.h"

PlaylistModel::PlaylistModel(Poco::SharedPtr<Playlist> pl)  : m_playlist{pl}
{
}

Poco::SharedPtr<Playlist> PlaylistModel::getPlaylist()
{
  return m_playlist;
}
