//
// Created by Вера on 17.12.2022.
//

#include "headers/SharedLibrary.h"

SharedLibrary::SharedLibrary(Poco::SharedPtr<DataBase> dataBase) : m_dataBase{dataBase}, DBWorker(dataBase->getSession())
{}


std::vector<Song> SharedLibrary::getAllSongs()
{
    std::vector<Song> songs;
    bool isPublic = true;

    std::vector<int> id; std::vector<std::string> name, performers, albums, audio;
    Poco::Data::Statement get(*m_session);
    get << "SELECT songs.id, songs.name, performers.nickname, albums.name, songs.audio FROM songs "
           "JOIN albums ON albums.id = songs.album_id "
           "JOIN performers ON performers.id = songs.performer_id "
           "WHERE albums.isPublic = $1",
            use(isPublic),
            into(id),
            into(name),
            into(performers),
            into(albums),
            into(audio);
    get.execute();

    for (int i{}; i < id.size(); ++i)
        songs.emplace_back(id[i], name[i], performers[i], albums[i], audio[i], m_dataBase);

    return songs;
}

//std::vector<Song> SharedLibrary::getSongsByGenre(int genreId)
//{
//  std::vector<Song> songs;
//  bool isPublic = true;

//  std::vector<int> id; std::vector<std::string> name, performers, albums, audio;
//  Poco::Data::Statement get(*m_session);
//  get << "SELECT songs.id, songs.name, performers.nickname, albums.name, songs.audio FROM songs "
//         "JOIN albums ON albums.id = songs.album_id "
//         "JOIN performers ON performers.id = songs.performer_id "
//         "WHERE albums.isPublic = $1 AND songs.genre_id = $2",
//      use(isPublic),
//      use(genreId),
//      into(id),
//      into(name),
//      into(performers),
//      into(albums),
//      into(audio);
//  get.execute();

//  for (int i{}; i < id.size(); ++i)
//    songs.emplace_back(id[i], name[i], performers[i], albums[i], audio[i], m_dataBase);

//  return songs;
//}

std::vector<Genre> SharedLibrary::getAllGenres()
{
  std::vector<int> ides;
  std::vector<Genre> genres;

  Poco::Data::Statement get(*m_session);
  get << "SELECT genres.id FROM genres ",
      into(ides);
  get.execute();

  for (const auto&id : ides)
    genres.push_back(Genre(id, m_dataBase));
  return genres;
}

const Poco::SharedPtr<DataBase> &SharedLibrary::dataBase() const
{
  return m_dataBase;
}

void SharedLibrary::setDataBase(const Poco::SharedPtr<DataBase> &newDataBase)
{
  m_dataBase = newDataBase;
}


std::vector<Album> SharedLibrary::getAllAlbums()
{
    std::vector<Album> albums;
    bool isPublic = true;

    std::vector<std::string> name, namePerformers;
    Poco::Data::Statement get(*m_session);
    get << "SELECT albums.name, performers.nickname FROM albums "
           "JOIN performers ON albums.performer_id = performers.id "
           "WHERE albums.isPublic = $1",
            use(isPublic),
            into(name),
            into(namePerformers);
    get.execute();

    for (int i{}; i < name.size(); ++i)
        albums.emplace_back(name[i], namePerformers[i], m_dataBase);

    return albums;
}

std::vector<Performer> SharedLibrary::getAllPerformers()
{
    std::vector<Performer> performers;

    std::vector<std::string> name;
    Poco::Data::Statement get(*m_session);
    get << "SELECT performers.nickname FROM performers",
            into(name);
    get.execute();

    for (int i{}; i < name.size(); ++i)
        performers.emplace_back(name[i], m_dataBase);

    return performers;
}

std::vector<Playlist> SharedLibrary::getAllPlaylists()
{
    std::vector<Playlist> playlists;

    bool isPublic = true;

    std::vector<std::string> name, nameUsers;
    Poco::Data::Statement get(*m_session);
    get <<"SELECT playlists.name, users.nickname FROM playlists "
           "JOIN Users ON playlists.user_id = users.id "
           "WHERE  playlists.isPublic = $1",
            use(isPublic),
            into(name),
            into(nameUsers);
    get.execute();

    for (int i{}; i < name.size(); ++i)
        playlists.emplace_back(nameUsers[i], name[i], m_dataBase);

    return playlists;
}

std::vector<User> SharedLibrary::getAllUsers()
{
    std::vector<User> users;
    bool isPublic = true;

    std::set<std::string> names;
    Poco::Data::Statement get(*m_session);
    get << "SELECT users.nickname FROM users "
           "JOIN playlists ON playlists.user_id = users.id "
           "WHERE playlists.isPublic = $1",
            use(isPublic),
            into(names);
    get.execute();

    for (const auto& name : names)
        users.emplace_back(name, m_dataBase);

    return users;
}

std::vector<Category> SharedLibrary::getAllCategories()
{
    std::vector<Category> categories;

    std::vector<int> id;
    Poco::Data::Statement get(*m_session);
    get << "SELECT categories.id FROM categories",
            into(id);
    get.execute();

    for (const auto& i : id)
        categories.emplace_back(i, m_dataBase);

    return categories;
}
