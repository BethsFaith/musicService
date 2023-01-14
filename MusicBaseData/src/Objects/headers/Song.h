//
// Created by Вера on 17.12.2022.
//

#ifndef MUSICBASEDATA_SONG_H
#define MUSICBASEDATA_SONG_H

#include "../../General/headers/DataBase.h"

class Song: public DBWorker
{
public:
    Song(int id, std::string name, std::string performer, std::string nameAlbum, Poco::SharedPtr <DataBase> dataBase);

    Song(std::string name, std::string performer, Poco::SharedPtr <DataBase> dataBase);

    Song(int id, Poco::SharedPtr <DataBase> dataBase);

    std::string getName();

    std::string getAlbumName();

    std::string getPerformerName();

    int getId();

    int getAlbumId();

    int getPerformerId();

    void setName(std::string name);

    void setFeat(std::string PerformerNickname);

    void setFeat(int Performer_id);

    bool isLiked(const std::string &loginUser);

    const Poco::SharedPtr <DataBase> &dataBase() const;

    void setDataBase(const Poco::SharedPtr <DataBase> &newDataBase);

private:
    int m_id;
    std::string m_name;
    std::string m_performer;
    std::string m_album;
    std::string m_genre;

    Poco::SharedPtr <DataBase> m_dataBase;

    const std::string NAME_TABLE = TABLES::Songs;
};

#endif //MUSICBASEDATA_SONG_H
