//
// Created by Вера on 10.12.2022.
//

#include "headers/DataBase.h"

DataBase::DataBase() {
    Poco::Data::PostgreSQL::Connector::registerConnector();
    m_session = Poco::makeShared<Poco::Data::Session>
            (Poco::Data::Session(Poco::Data::PostgreSQL::Connector::KEY,
                                 "host=localhost user=postgres port=5432 password=1611 dbname=Music_Service"));
}

void DataBase::insertUser(std::string _login, std::string _nickname, std::string _pass, bool _isModerator) {
    Poco::Data::Statement insert(*m_session);
    insert << "INSERT INTO users(nickname, login, password, is_moderator) VALUES($1, $2, $3, $4)",
            use(_nickname),
            use(_login),
            use(_pass),
            use(_isModerator);

    insert.execute();
}

void DataBase::insertPerformer(std::string login, std::string nickname, std::string pass) {
    Poco::Data::Statement insert(*m_session);
    insert << "INSERT INTO performers(nickname, login, password) VALUES($1, $2, $3)",
            use(nickname),
            use(login),
            use(pass);

    insert.execute();
}

void DataBase::insertGenre(std::string name) {
    Poco::Data::Statement insert(*m_session);
    insert << "INSERT INTO genres(name) VALUES($1)",
            use(name);

    insert.execute();
}

void DataBase::insertSong(std::string name, std::string genreName, std::string albumName,
                          std::string performerName) {
    int genreId = getGenreId(genreName),
        albumId = getAlbumId(albumName, performerName),
        performerId = getPerformerIdByNickname(performerName);

    Poco::Data::Statement insert(*m_session);
    insert << "INSERT INTO songs(name, performer_id, album_id, genre_id) VALUES($1, $2, $3, $4)",
            use(name),
            use(performerId),
            use(albumId),
            use(genreId);

    insert.execute();
}

void DataBase::insertAlbum(std::string name, const std::string &performerName, std::string coverArt, bool isPublic) {
    int performerId = getPerformerIdByNickname(performerName);
    Poco::Timestamp timeS;
    auto time = Poco::Data::Time(timeS);

    Poco::Data::Statement insert(*m_session);
    insert
            << "INSERT INTO albums(name, performer_id, coverArt, date, isPublic) VALUES($1, $2, $3, current_timestamp, $4)",
            use(name),
            use(performerId),
            use(coverArt),
            use(isPublic);

    insert.execute();
}

void DataBase::insertPlaylist(std::string name, const std::string &userName, std::string coverArt, bool isPublic) {
    int userId = getUserIdByNickname(userName);
    Poco::Timestamp timeS;
    auto time = Poco::Data::Time(timeS);
    Poco::Data::Statement insert(*m_session);
    insert
            << "INSERT INTO playlists(name, user_id, coverArt, date, ispublic) VALUES($1, $2, $3, current_timestamp, $4)",
            use(name),
            use(userId),
            use(coverArt),
            use(isPublic);

    insert.execute();
}

void DataBase::insertCategory(std::string name, std::string picture) {
    Poco::Data::Statement insert(*m_session);
    insert << "INSERT INTO Categories(name, coverArt) VALUES($1, $2)",
            use(name),
            use(picture);

    insert.execute();
}

int DataBase::getAlbumId(std::string name, const std::string &performerName) {
    int id{};
    int perf_id{getPerformerIdByNickname(performerName)};
    select("id", TABLES::Albums, "name", name, "performer_id", std::to_string(perf_id), id);
    return id;
}

int DataBase::getPerformerIdByNickname(std::string name) {
    int id{};
    select<int>("id", TABLES::Performers, "nickname", name, id);
    return id;
}

int DataBase::getPerformerIdByLogin(std::string login) {
    int id{};
    select<int>("id", TABLES::Performers, "login", login, id);
    return id;
}

int DataBase::getUserIdByNickname(std::string nickName) {
    int id{};
    select<int>("id", TABLES::Users, "nickname", nickName, id);
    return id;
}

int DataBase::getUserIdByLogin(std::string login) {
    int id{};
    select<int>("id", TABLES::Users, "login", login, id);
    return id;
}

int DataBase::getGenreId(std::string name) {
    int id{};
    select<int>("id", TABLES::Genres, "name", name, id);

    return id;
}

std::vector <std::string> DataBase::getSongsByPerformer(std::string performerName) {
    std::vector <std::string> songs{};
    Poco::Data::Statement get(*m_session);
    get << "SELECT songs.name FROM songs "
           "JOIN performers ON performers.Id = songs.performer_id "
           "WHERE performers.nickname = $1",
            use(performerName),
            into(songs);
    get.execute();

    return songs;
}

int DataBase::getSongId(std::string name, const std::string &performerName) {
    int id{}, performer_id{getPerformerIdByNickname(performerName)};
    select<int>("id", TABLES::Songs, "name", name, "performer_id", std::to_string(performer_id), id)

    return id;
}

int DataBase::getCategoryId(std::string name) {
    int id{};
    select("id", TABLES::Categories, "name", name, id);
    return id;
}


int DataBase::getPlaylistId(std::string name, const std::string &userName) {
    int id{}, user_id{getUserIdByNickname(userName)};

    select("id", TABLES::Playlists, "name", name, "user_id", std::to_string(user_id), id);

    return id;
}

Poco::SharedPtr <Poco::Data::Session> DataBase::getSession() {
    return m_session;
}

bool DataBase::checkUserPass(std::string login, std::string pass) {
    int user_id = getUserIdByLogin(login);
    return checkValueById("password", TABLES::Users, user_id, pass);
}

bool DataBase::checkPerformerPass(std::string login, std::string pass) {
    int performer_id = getPerformerIdByLogin(login);
    return checkValueById("password", TABLES::Performers, performer_id, pass);
}

void DataBase::deleteSong(int songId) {
    remove(TABLES::Songs, "id", songId);
}

void DataBase::deleteAlbum(int albumId) {
    remove(TABLES::Albums, "id", albumId);
}

void DataBase::deleteUser(int userId) {
    remove(TABLES::Users, "id", userId);
}

void DataBase::deletePerformer(int userId) {
    remove(TABLES::Performers, "id", userId);
}

void DataBase::deleteCategory(int categoryId) {
    remove(TABLES::Categories, "id", categoryId);
}

void DataBase::deletePlaylist(int playlistId) {
    remove(TABLES::Playlists, "id", playlistId);
}
