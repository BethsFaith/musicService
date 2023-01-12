//
// Created by Вера on 16.12.2022.
//

#ifndef MUSICBASEDATA_PLAYLIST_H
#define MUSICBASEDATA_PLAYLIST_H

#include "../../General/headers/DataBase.h"
#include "Song.h"

class Playlist : public DBWorker
{
public:
    Playlist(const std::string& createrName, const std::string& playlistName, Poco::SharedPtr<DataBase> dataBase);
    Playlist(const int& id, Poco::SharedPtr<DataBase> dataBase);

    void addSong(int songId);
    void addSong(const std::string& songName, const std::string& performerName);

    void removeSong(int songId);
    void removeSong(const std::string& songName, const std::string& performerName);

    void setName(std::string newName);
    void setCoverArt(std::string newCoverArtRef);

    std::vector<Song> getSongs();

    const std::string& getName();
    const int& getId();
    const std::string& getUserNickname();
    const std::string& getCoverArtRef();

    void setPublic(bool x);

    Poco::SharedPtr<DataBase> getDb();

    bool isPublic();
private:
    int m_id;
    std::string m_name;
    std::string m_user;
    std::string m_coverArtRef;
    bool m_isPublic;

    Poco::SharedPtr<DataBase> m_dataBase;

    const std::string NAME_TABLE = TABLES::Playlists;
};

#endif //MUSICBASEDATA_PLAYLIST_H
