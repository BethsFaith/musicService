//
// Created by Вера on 21.12.2022.
//

#include "headers/Category.h"

Category::Category(const std::string &name, const std::string &coverArt, Poco::SharedPtr <DataBase> dataBase)
        : DBWorker{dataBase->getSession()}, m_name{name}, m_coverArt{coverArt}, m_dataBase{dataBase} {
    m_id = m_dataBase->getCategoryId(name);
    if (m_id == 0)
        throw Poco::Exception("category doesn't exist");
}

Category::Category(int id, Poco::SharedPtr <DataBase> dataBase) : DBWorker{dataBase->getSession()}, m_id{id},
                                                                  m_dataBase{dataBase} {
    if (m_id == 0)
        throw Poco::Exception("category doesn't exist");

    selectById("name", NAME_TABLE, m_id, m_name);
    selectById("coverArt", NAME_TABLE, m_id, m_coverArt);
}

void Category::addPlaylist(int playlistId) {
    Poco::Data::Statement insert(*m_session);
    insert << Poco::format(R"(INSERT INTO %s(category_id, playlist_id) valurs (%'d','%d'))",
                           TABLES::B_Category_Playlist, m_id, playlistId);
    insert.execute();
}

void Category::removePlaylist(int playlistId) {
    remove(TABLES::B_Category_Playlist, "category_id", m_id, "playlist_id", playlistId);
}

std::string Category::getName() {
    return m_name;
}

std::string Category::getCoverArt() {
    return m_coverArt;
}

std::vector <Playlist> Category::getPlaylists() {
    std::vector <Playlist> playlists;

    bool isPublic = true;

    std::vector <std::string> name, nameUsers;
    Poco::Data::Statement get(*m_session);
    get << "SELECT playlists.name, users.nickname FROM bond_categoriesplaylists "
           "JOIN Playlists ON playlists.id =  bond_categoriesplaylists.playlist_id "
           "JOIN Users ON playlists.user_id = users.id  "
           "WHERE bond_categoriesplaylists.category_id = $1 AND playlists.isPublic = $2 ",
            use(m_id),
            use(isPublic),
            into(name),
            into(nameUsers);
    get.execute();

    for (int i{}; i < nameUsers.size(); ++i)
        playlists.emplace_back(nameUsers[i], name[i], m_dataBase);

    return playlists;
}

void Category::setName(const std::string &name) {
    update(NAME_TABLE, "name", name, m_id);
    m_name = name;
}

void Category::setCoverArt(const std::string &coverArt) {
    update(NAME_TABLE, "coverArt", coverArt, m_id);
    m_coverArt = coverArt;
}

Poco::SharedPtr <DataBase> Category::getDB() {
    return m_dataBase;
}
