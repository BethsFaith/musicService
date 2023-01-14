//
// Created by Вера on 17.12.2022.
//

#include "headers/UserLibrary.h"

UserLibrary::UserLibrary(int userId, Poco::SharedPtr <DataBase> dataBase) : m_userId{userId}, m_dataBase{dataBase},
                                                                            DBWorker(dataBase->getSession()) {
}

std::vector <Playlist> UserLibrary::getPlaylists() {
    std::vector <Playlist> playlists;

    bool isLiked = true;

    std::vector<int> id;
    std::vector <std::string> name, nameUsers;
    Poco::Data::Statement get(*m_session);
    get << "SELECT playlists.name, users.nickname FROM playlists "
           "JOIN likedPlaylists ON likedPlaylists.playlist_id = playlists.id "
           "JOIN Users ON playlists.user_id = users.id "
           "WHERE likedPlaylists.user_id = $1 AND likedPlaylists.is_liked = $2",
            use(m_userId),
            use(isLiked),
            into(name),
            into(nameUsers);
    get.execute();

    for (int i{}; i < id.size(); ++i)
        playlists.emplace_back(nameUsers[i], name[i], m_dataBase);

    return playlists;
}

std::vector <Song> UserLibrary::getSongs() {
    std::vector <Song> songs;
    bool isLiked = true;

    std::vector<int> id;
    std::vector <std::string> name, performers, albums;
    Poco::Data::Statement get(*m_session);
    get << "SELECT songs.id, songs.name, performers.nickname, albums.name FROM songs "
           "JOIN likedSongs ON likedSongs.song_id = songs.id "
           "JOIN albums ON albums.id = songs.album_id "
           "JOIN performers ON performers.id = songs.performer_id "
           "WHERE likedSongs.user_id = $1 AND likedSongs.is_liked = $2",
            use(m_userId),
            use(isLiked),
            into(id),
            into(name),
            into(performers),
            into(albums);
    get.execute();

    for (int i{}; i < id.size(); ++i)
        songs.emplace_back(id[i], name[i], performers[i], albums[i], m_dataBase);

    return songs;
}

std::vector <Performer> UserLibrary::getPerformers() {
    std::vector <Performer> performers;
    bool isLiked = true;

    std::vector <std::string> name;
    Poco::Data::Statement get(*m_session);
    get << "SELECT performers.nickname FROM performers "
           "JOIN likedPerformers ON likedPerformers.performer_id = performers.id "
           "WHERE likedPerformers.user_id = $1 AND likedPerformers.is_liked = $2",
            use(m_userId),
            use(isLiked),
            into(name);
    get.execute();

    for (int i{}; i < name.size(); ++i)
        performers.emplace_back(name[i], m_dataBase);

    return performers;
}

std::vector <Album> UserLibrary::getAlbums() {
    std::vector <Album> albums;

    bool isLiked = true;

    std::vector <std::string> name, namePerformers;
    Poco::Data::Statement get(*m_session);
    get << "SELECT albums.name, performers.nickname FROM albums "
           "JOIN likedAlbums ON likedAlbums.Album_id = albums.id "
           "JOIN performers ON albums.performer_id = performers.id "
           "WHERE likedAlbums.user_id = $1 AND likedAlbums.is_liked = $2",
            use(m_userId),
            use(isLiked),
            into(name),
            into(namePerformers);
    get.execute();

    for (int i{}; i < name.size(); ++i)
        albums.emplace_back(name[i], namePerformers[i], m_dataBase);

    return albums;
}

std::vector <Playlist> UserLibrary::getOwnPlaylists() {
    std::vector <Playlist> playlists;

    bool isLiked = true;

    std::vector <std::string> name;
    Poco::Data::Statement get(*m_session);
    get << "SELECT playlists.name FROM playlists "
           "JOIN Users ON playlists.user_id = users.id "
           "WHERE playlists.user_id = $1",
            use(m_userId),
            into(name);
    get.execute();

    std::string nameUser;
    selectById<std::string>("nickname", TABLES::Users, m_userId, nameUser);
    for (int i{}; i < name.size(); ++i)
        playlists.emplace_back(nameUser, name[i], m_dataBase);

    return playlists;
}
