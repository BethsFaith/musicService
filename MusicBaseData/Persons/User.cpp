//
// Created by Вера on 17.12.2022.
//

#include "headers/User.h"

User::User(const std::string nickname, Poco::SharedPtr <DataBase> dataBase) : m_nickname{nickname},
                                                                              m_dataBase{dataBase},
                                                                              DBWorker(dataBase->getSession()) {
    m_id = m_dataBase->getUserIdByNickname(nickname);
    if (m_id == 0)
        throw Poco::Exception("user doesn't exist");
    m_userLibrary = Poco::makeShared<UserLibrary>(m_id, m_dataBase);
}

User::User(int id, Poco::SharedPtr <DataBase> dataBase) : m_id{id}, m_dataBase{dataBase},
                                                          DBWorker(dataBase->getSession()) {
    if (m_id == 0)
        throw Poco::Exception("user doesn't exist");
    selectById("nickname", NAME_TABLE, m_id, m_nickname);
    m_userLibrary = Poco::makeShared<UserLibrary>(m_id, m_dataBase);
}

void User::setNickname(std::string nickname) {
    update(NAME_TABLE, "nickname", nickname, m_id);
    m_nickname = nickname;
}

void User::setPassword(std::string pass) {
    update(NAME_TABLE, "password", pass, m_id);
}

void User::rateSong(int songId, bool rate) {
    int id{};
    select("id", "likedsongs", "song_id", std::to_string(songId), "user_id", std::to_string(m_id), id);
    if (id != 0)
        update("likedsongs", "is_liked", std::to_string(rate), id);
    else {
        Poco::Data::Statement insert(*m_dataBase->getSession());
        insert << "INSERT INTO likedSongs(song_id, user_id, is_liked, date) VALUES ($1,$2, $3, current_timestamp)",
                use(songId),
                use(m_id),
                use(rate);
        insert.execute();
    }
}

void User::ratePerformer(int performerId, bool rate) {
    int id{};
    select("id", "likedperformers", "performer_id", std::to_string(performerId), "user_id", std::to_string(m_id), id);
    if (id != 0)
        update("likedperformers", "is_liked", std::to_string(rate), id);
    else {
        Poco::Data::Statement insert(*m_dataBase->getSession());
        insert
                << "INSERT INTO likedPerformers(performer_id, user_id, is_liked, date) VALUES ($1,$2, $3, current_timestamp)",
                use(performerId),
                use(m_id),
                use(rate);
        insert.execute();
    }
}

void User::ratePlaylist(int playlistId, bool rate) {
    int id{};
    select("id", "likedplaylists", "playlist_id", std::to_string(playlistId), "user_id", std::to_string(m_id), id);
    if (id != 0)
        update("likedplaylists", "is_liked", std::to_string(rate), id);
    else {
        Poco::Data::Statement insert(*m_dataBase->getSession());
        insert
                << "INSERT INTO likedPlaylists(playlist_id, user_id, is_liked, date) VALUES ($1,$2, $3, current_timestamp)",
                use(playlistId),
                use(m_id),
                use(rate);
        insert.execute();
    }
}

void User::rateAlbum(int albumId, bool rate) {
    int id{};
    select("id", "likedalbums", "album_id", std::to_string(albumId), "user_id", std::to_string(m_id), id);
    if (id != 0)
        update("likedalbums", "is_liked", std::to_string(rate), id);
    else {
        Poco::Data::Statement insert(*m_dataBase->getSession());
        insert << "INSERT INTO likedAlbums(album_id, user_id, is_liked, date) VALUES ($1,$2, $3, current_timestamp)",
                use(albumId),
                use(m_id),
                use(rate);
        insert.execute();
    }
}

std::vector <Playlist> User::getPlaylists() {
//  return m_userLibrary->getOwnPlaylists();
    std::vector <Playlist> playlists;

    bool isPublic = true;

    std::vector <std::string> name;
    Poco::Data::Statement get(*m_session);
    get << "SELECT playlists.name FROM playlists "
           "JOIN Users ON playlists.user_id = users.id "
           "WHERE playlists.user_id = $1 AND playlists.isPublic = $2",
            use(m_id),
            use(isPublic),
            into(name);
    get.execute();

    for (int i{}; i < name.size(); ++i)
        playlists.emplace_back(m_nickname, name[i], m_dataBase);

    return playlists;
}

Poco::SharedPtr <UserLibrary> User::getUserLibrary() {
    return m_userLibrary;
}

Poco::SharedPtr <DataBase> User::getDataBase() {
    return m_dataBase;
}

std::string User::getNick() {
    return m_nickname;
}

std::string User::getLogin() {
    std::string login;
    selectById("login", NAME_TABLE, m_id, login);
    return login;
}

bool User::isModerator() {
    bool isModerator;
    selectById("is_moderator", NAME_TABLE, m_id, isModerator);
    return isModerator;
}
