//
// Created by Вера on 21.12.2022.
//

#ifndef MUSICBASEDATA_CATEGORY_H
#define MUSICBASEDATA_CATEGORY_H

#include "../../General/headers/DataBase.h"
#include "Playlist.h"
#include "Song.h"

class Category : public DBWorker
{
public:
    Category(const std::string& name, const std::string& coverArt, Poco::SharedPtr<DataBase> dataBase);
    Category(int id,Poco::SharedPtr<DataBase> dataBase);

    void addPlaylist(int playlistId);
    void removePlaylist(int playlistId);

    std::string getName();
    std::string getCoverArt();

    std::vector<Playlist> getPlaylists();

    void setName(const std::string& name);
    void setCoverArt(const std::string& coverArt);

    Poco::SharedPtr<DataBase> getDB();
protected:
    Poco::SharedPtr<DataBase> m_dataBase;
    const std::string NAME_TABLE = TABLES::Categories;

private:
    std::string m_coverArt;
    std::string m_name;
    int m_id;
};

#endif //MUSICBASEDATA_CATEGORY_H
