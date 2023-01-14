//
// Created by Вера on 17.12.2022.
//

#include "headers/Performer.h"

Performer::Performer(const std::string nickname, Poco::SharedPtr <DataBase> dataBase) : m_nickname{nickname},
                                                                                        m_dataBase{dataBase}, DBWorker(
                dataBase->getSession()) {
    m_id = m_dataBase->getPerformerIdByNickname(nickname);
    if (m_id == 0)
        throw Poco::Exception("performer doesn't exist");
}

Performer::Performer(int id, Poco::SharedPtr <DataBase> dataBase) : m_dataBase{dataBase},
                                                                    DBWorker(dataBase->getSession()), m_id{id} {
    if (m_id == 0)
        throw Poco::Exception("performer doesn't exist");
    selectById("nickname", NAME_TABLE, m_id, m_nickname);
}

std::vector <Song> Performer::getSongs() {
    std::vector <Song> songs;

    std::vector<int> id;
    std::vector <std::string> name, performers, albums;
    Poco::Data::Statement get(*m_session);
    get << "SELECT songs.id, songs.name, albums.name FROM songs "
           "JOIN performers ON performers.id = songs.performer_id "
           "JOIN albums ON albums.id = songs.album_id "
           "WHERE performers.id = $1",
            use(m_id),
            into(id),
            into(name),
            into(albums);
    get.execute();

    for (int i{}; i < id.size(); ++i)
        songs.emplace_back(id[i], name[i], m_nickname, albums[i], m_dataBase);

    return songs;
}

std::vector <Album> Performer::getAlbums() {
    std::vector <Album> albums;

    std::vector <std::string> name;
    Poco::Data::Statement get(*m_session);
    get << "SELECT albums.name FROM albums "
           "JOIN performers ON performers.id = albums.performer_id "
           "WHERE performers.id = $1",
            use(m_id),
            into(name);
    get.execute();

    for (int i{}; i < name.size(); ++i)
        albums.emplace_back(name[i], m_nickname, m_dataBase);

    return albums;
}

void Performer::setNickname(std::string nickname) {
    update(NAME_TABLE, "nickname", nickname, m_id);
}

void Performer::setPassword(std::string pass) {
    update(NAME_TABLE, "password", pass, m_id);
}

Poco::SharedPtr <DataBase> Performer::dataBase() {
    return m_dataBase;
}

void Performer::setDataBase(Poco::SharedPtr <DataBase> newDataBase) {
    m_dataBase = newDataBase;
}

void Performer::addAlbum(std::string name, std::string coverArt) {
    m_dataBase->insertAlbum(name, m_nickname, coverArt);
}

void Performer::removeAlbum(std::string name) {
    m_dataBase->deleteAlbum(m_dataBase->getAlbumId(name, m_nickname));
}

std::string Performer::getName() {
    return m_nickname;
}
