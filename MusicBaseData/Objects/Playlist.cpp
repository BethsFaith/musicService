//
// Created by Вера on 16.12.2022.
//

#include "headers/Playlist.h"

Playlist::Playlist(const std::string &createrName, const std::string &playlistName,
                   Poco::SharedPtr <DataBase> dataBase) : m_dataBase{dataBase}, m_user{createrName},
                                                          m_name{playlistName},
                                                          DBWorker{dataBase->getSession()} {
    m_id = m_dataBase->getPlaylistId(m_name, m_user);
    if (m_id == 0)
        throw Poco::Exception("playlist doesn't exist");

    selectById<bool>("isPublic", NAME_TABLE, m_id, m_isPublic);
    selectById<std::string>("coverArt", NAME_TABLE, m_id, m_coverArtRef);
}

Playlist::Playlist(const int &id, Poco::SharedPtr <DataBase> dataBase) : m_id{id}, DBWorker{dataBase->getSession()},
                                                                         m_dataBase{dataBase} {
    if (m_id == 0)
        throw Poco::Exception("playlist doesn't exist");

    selectById<bool>("isPublic", NAME_TABLE, m_id, m_isPublic);
    selectById<std::string>("name", NAME_TABLE, m_id, m_name);
    int userId{};
    selectById<int>("user_id", NAME_TABLE, m_id, userId);
    selectById<std::string>("nickname", TABLES::Users, userId, m_user);
    selectById<std::string>("coverArt", NAME_TABLE, m_id, m_coverArtRef);
}

void Playlist::addSong(int songId) {
    Poco::Data::Statement insert(*m_dataBase->getSession());
    insert << "INSERT INTO bond_songsplaylists(song_id, playlist_id) VALUES ($1,$2)",
            use(songId),
            use(m_id);
    insert.execute();
}

void Playlist::addSong(const std::string &songName, const std::string &performerName) {
    addSong(m_dataBase->getSongId(songName, performerName));
}

void Playlist::removeSong(int songId) {
    remove(TABLES::B_Song_Playlist, "song_id", songId, "playlist_id", m_id);
}

void Playlist::removeSong(const std::string &songName, const std::string &performerName) {
    removeSong(m_dataBase->getSongId(songName, performerName));
}

void Playlist::setName(std::string newName) {
    update(NAME_TABLE, "name", newName, m_id);
    m_name = newName;
}

void Playlist::setCoverArt(std::string newCoverArtRef) {
    update(NAME_TABLE, "coverArt", newCoverArtRef, m_id);
    m_coverArtRef = newCoverArtRef;
}

std::vector <Song> Playlist::getSongs() {
    std::vector <Song> songs;

    std::vector<int> id;
    std::vector <std::string> name, performers, albums;
    Poco::Data::Statement get(*m_session);
    get
            << "SELECT songs.id, songs.name, performers.nickname as Performer, albums.name as Album FROM bond_songsplaylists "
               "JOIN songs ON songs.id = bond_songsplaylists.song_id "
               "JOIN performers ON performers.id = songs.performer_id "
               "JOIN albums ON albums.id = songs.album_id "
               "WHERE bond_songsplaylists.playlist_id = $1",
            use(m_id),
            into(id),
            into(name),
            into(performers),
            into(albums);
    get.execute();

    for (int i{}; i < id.size(); ++i)
        songs.emplace_back(id[i], name[i], performers[i], albums[i], m_dataBase);

    return songs;
}

const int &Playlist::getId() {
    return m_id;
}

const std::string &Playlist::getName() {
    return m_name;
}

const std::string &Playlist::getUserNickname() {
    return m_user;
}

bool Playlist::isPublic() {
    return m_isPublic;
}

const std::string &Playlist::getCoverArtRef() {
    return m_coverArtRef;
}

void Playlist::setPublic(bool x) {
    m_isPublic = x;
    update(NAME_TABLE, "isPublic", std::to_string(x), m_id);
}

Poco::SharedPtr <DataBase> Playlist::getDb() {
    return m_dataBase;
}
