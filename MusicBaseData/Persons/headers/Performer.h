//
// Created by Вера on 17.12.2022.
//

#ifndef MUSICBASEDATA_PERFORMER_H
#define MUSICBASEDATA_PERFORMER_H

#include "../../General/headers/DataBase.h"
#include "../../Objects/headers/Song.h"
#include "../../Objects/headers/Album.h"

class Performer: public DBWorker
{
public:
    Performer(const std::string nickname, Poco::SharedPtr <DataBase> dataBase);

    Performer(int id, Poco::SharedPtr <DataBase> dataBase);

    std::vector <Song> getSongs();

    std::vector <Album> getAlbums();

    std::string getName();

    void addAlbum(std::string name, std::string coverArt);

    void removeAlbum(std::string name);

    void setNickname(std::string nickname);

    void setPassword(std::string pass);

    Poco::SharedPtr <DataBase> dataBase();

    void setDataBase(Poco::SharedPtr <DataBase> newDataBase);

private:
    std::string m_nickname;
    int m_id;

    Poco::SharedPtr <DataBase> m_dataBase;

    const std::string NAME_TABLE = TABLES::Performers;
};

#endif //MUSICBASEDATA_PERFORMER_H
