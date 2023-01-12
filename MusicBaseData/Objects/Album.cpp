//
// Created by Вера on 17.12.2022.
//

#include "headers/Album.h"

Album::Album(int id, Poco::SharedPtr<DataBase> dataBase) : m_id{id}, m_dataBase{dataBase}
{
  if (m_id == 0)
    throw Poco::Exception("album doesn't exist");

  std::cout << m_id;
  selectById("name", NAME_TABLE, m_id, m_name);
  std::cout << m_name;

  int perfId{};
  selectById<int> ("performer_id", NAME_TABLE, m_id, perfId);
    std::cout << perfId;
  selectById<std::string > ("nickname", TABLES::Performers, perfId, m_performer);
  std::cout << m_performer;

  selectById("isPublic", NAME_TABLE, m_id, m_isPublic);
  selectById("coverArt", NAME_TABLE, m_id, m_coverArtRef);
}

Album::Album(std::string name, std::string performer, Poco::SharedPtr<DataBase> dataBase) : m_name{name}, m_performer{performer}, m_dataBase{dataBase}, DBWorker{dataBase->getSession()}
{
  select("id", NAME_TABLE, "performer_id", std::to_string(m_dataBase->getPerformerIdByNickname(performer)), "name", name, m_id);
  if (m_id == 0)
    throw Poco::Exception("album doesn't exist");

  selectById("isPublic", NAME_TABLE, m_id, m_isPublic);
  selectById("coverArt", NAME_TABLE, m_id, m_coverArtRef);
}

void Album::removeSong(int songId)
{
    if (!checkValueById("album_id", "songs", songId, m_id))
        throw Poco::Exception("no song in this album");
    m_dataBase->deleteSong(songId);
}

void Album::removeSong(const std::string &songName)
{
    int id = m_dataBase->getSongId(songName, m_performer);
    removeSong(id);
}

void Album::setName(std::string newName)
{
    update(NAME_TABLE, "name", newName, m_id);
    m_name = newName;
}

void Album::setCoverArt(std::string newCoverArtRef)
{
    update(NAME_TABLE, "coverArt", newCoverArtRef, m_id);
    m_coverArtRef = newCoverArtRef;
}

void Album::toPublish()
{
    update(NAME_TABLE, "isPublic", std::to_string(true), m_id);
    m_isPublic = true;
}

std::vector<Song> Album::getSongs()
{
    std::vector<Song> songs;

    std::vector<int> id; std::vector<std::string> name, performers, audio;
    Poco::Data::Statement get(*m_session);
    get << "SELECT songs.id, songs.name, performers.nickname as Performer, songs.audio FROM songs "
           "JOIN albums ON albums.id = songs.album_id "
           "JOIN performers ON performers.id = songs.performer_id "
           "WHERE albums.id = $1",
            use(m_id),
            into(id),
            into(name),
            into(performers),
            into(audio);
    get.execute();

    for (int i{}; i < id.size(); ++i)
        songs.emplace_back(id[i], name[i], performers[i], m_name, audio[i], m_dataBase);

    return songs;
}

const std::string &Album::getName()
{
    return m_name;
}

const int &Album::getId()
{
    return m_id;
}

const std::string &Album::getPerformerNickname()
{
    return m_performer;
}

bool Album::isPublic()
{
    return m_isPublic;
}

const std::string &Album::getCoverArtRef()
{
  return m_coverArtRef;
}

Poco::SharedPtr<DataBase> Album::getDB()
{
  return m_dataBase;
}
