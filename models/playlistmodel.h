#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include "../base/basemodel.h"
#include "../MusicBaseData/Objects/headers/Playlist.h"
#include "../MusicBaseData/Objects/headers/Song.h"

class PlaylistModel : public BaseModel
{
public:
  PlaylistModel(Poco::SharedPtr<Playlist> pl);

  Poco::SharedPtr<Playlist> getPlaylist();
private:
  Poco::SharedPtr<Playlist> m_playlist;
};

#endif // PLAYLISTMODEL_H
