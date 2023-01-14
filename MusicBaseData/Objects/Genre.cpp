#include "headers/Genre.h"

Genre::Genre(int id, Poco::SharedPtr <DataBase> db) : DBWorker{db->getSession()}, m_id{id}, m_dataBase{db} {
    if (m_id == 0)
        throw Poco::Exception("genre doesn't exist");

    selectById("name", NAME_TABLE, m_id, m_name);
    selectById("coverArt", NAME_TABLE, m_id, m_coverArt);
}

const std::string &Genre::name() const {
    return m_name;
}

void Genre::setName(const std::string &newName) {
    update(NAME_TABLE, "name", newName, m_id);
    m_name = newName;
}

const std::string &Genre::cover_art() const {
    return m_coverArt;
}

void Genre::setCover_art(const std::string &newCover_art) {
    update(NAME_TABLE, "coverArt", newCover_art, m_id);
    m_coverArt = newCover_art;
}

std::vector <Song> Genre::getSongs() {
    std::vector <Song> songs;
    bool isPublic = true;

    std::vector<int> id;
    std::vector <std::string> name, performers, albums;
    Poco::Data::Statement get(*m_session);
    get << "SELECT songs.id, songs.name, performers.nickname, albums.name FROM songs "
           "JOIN albums ON albums.id = songs.album_id "
           "JOIN performers ON performers.id = songs.performer_id "
           "WHERE albums.isPublic = $1 AND songs.genre_id = $2",
            use(isPublic),
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

Poco::SharedPtr <DataBase> Genre::getDB() {
    return m_dataBase;
}
