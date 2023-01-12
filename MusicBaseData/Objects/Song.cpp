//
// Created by Вера on 17.12.2022.
//

#include "headers/Song.h"

Song::Song(int id, std::string name, std::string performer, std::string albumName, std::string audio, Poco::SharedPtr<DataBase> dataBase) : m_id{id}, m_name{name}, m_performer{performer}, m_album{albumName}, m_audio{audio}, m_dataBase{dataBase}, DBWorker{dataBase->getSession()}
{
    selectById("name", TABLES::Genres, m_id, m_genre);
}

Song::Song(std::string name, std::string performer, Poco::SharedPtr<DataBase> dataBase) : m_name{name}, m_performer{performer}, m_dataBase{dataBase}, DBWorker{dataBase->getSession()}
{
    m_id = m_dataBase->getSongId(m_name, m_performer);
    if (m_id == 0)
      throw Poco::Exception("song doesn't exist");

    selectById("name", TABLES::Albums, getAlbumId(), m_album);
}

Song::Song(int id, Poco::SharedPtr<DataBase> dataBase) : m_id{id}, m_dataBase{dataBase}, DBWorker{dataBase->getSession()}
{
    if (m_id == 0)
      throw Poco::Exception("song doesn't exist");

    selectById("name", NAME_TABLE, m_id, m_name);
    selectById("nickname", TABLES::Performers, getPerformerId(), m_performer);
    selectById("name", TABLES::Albums, getAlbumId(), m_album);
}

int Song::getAlbumId()
{
    int id{};
    selectById("album_id", NAME_TABLE, m_id, id);
    return id;
}

int Song::getPerformerId()
{
    int id{};
    selectById("performer_id", NAME_TABLE, m_id, id);
    return id;
}

void Song::setName(std::string name)
{
    update(NAME_TABLE, "name", name, m_id);
    m_name = name;
}

void Song::setFeat(std::string performerNickname)
{
    setFeat(m_dataBase->getPerformerIdByNickname(performerNickname));
}

void Song::setFeat(int performer_id)
{
    if (getPerformerId() == performer_id)
        throw Poco::Exception("main performer and additional performer cant be the same");

    Poco::Data::Statement insert(*m_dataBase->getSession());
    insert << "INSERT INTO feats(song_id, additionalperformer_id) VALUES ($1,$2)",
            use(m_id),
            use(performer_id);
    insert.execute();
}

bool Song::isLiked(const std::string &loginUser)
{
    bool isLiked;
    select("is_liked", TABLES::LikedSongs, "song_id", std::to_string(m_id), "user_id", std::to_string(m_dataBase->getUserIdByLogin(loginUser)), isLiked);
    return isLiked;
}

std::string Song::getName()
{
    return m_name;
}

std::string Song::getAlbumName()
{
    return m_album;
}

std::string Song::getPerformerName()
{
  return m_performer;
}

int Song::getId()
{
  return m_id;
}
