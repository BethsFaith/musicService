//
// Created by Вера on 17.12.2022.
//

#ifndef MUSICBASEDATA_ALBUM_H
#define MUSICBASEDATA_ALBUM_H

#include "../../General/headers/DataBase.h"
#include "Song.h"

class Album: public DBWorker
{
public:
//    Album(int id, std::string name, std::string performer, Poco::SharedPtr<DataBase> dataBase);
    Album(std::string name, std::string performer, Poco::SharedPtr <DataBase> dataBase);

    Album(int id, Poco::SharedPtr <DataBase> dataBase);

    void addSong(std::string name, std::string genreName);

    void removeSong(int songId);

    void removeSong(const std::string &songName);

    void setName(std::string newName);

    void setCoverArt(std::string newCoverArtRef);

    void toPublish();

    std::vector <Song> getSongs();

    const std::string &getName();

    const int &getId();

    const std::string &getPerformerNickname();

    const std::string &getCoverArtRef();

    Poco::SharedPtr <DataBase> getDB();

    bool isPublic();

private:
    int m_id;
    std::string m_name;
    std::string m_performer;
    std::string m_coverArtRef;
    bool m_isPublic;

    Poco::SharedPtr <DataBase> m_dataBase;

    const std::string NAME_TABLE = TABLES::Albums;
};


#endif //MUSICBASEDATA_ALBUM_H
