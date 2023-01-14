//
// Created by Вера on 17.12.2022.
//

#ifndef MUSICBASEDATA_USER_H
#define MUSICBASEDATA_USER_H

#include "../../General/headers/DataBase.h"
#include "../../Objects/headers/UserLibrary.h"

class User: public DBWorker
{
public:
    User(const std::string nickname, Poco::SharedPtr <DataBase> dataBase);

    User(int id, Poco::SharedPtr <DataBase> dataBase);

    void setNickname(std::string nickname);

    void setPassword(std::string pass);

    std::string getNick();

    std::string getLogin();

    void rateSong(int songId, bool rate);

    void ratePerformer(int performerId, bool rate);

    void ratePlaylist(int playlistId, bool rate);

    void rateAlbum(int albumId, bool rate);

    std::vector <Playlist> getPlaylists();

    Poco::SharedPtr <UserLibrary> getUserLibrary();

    Poco::SharedPtr <DataBase> getDataBase();

    bool isModerator();

private:
    std::string m_nickname;
    int m_id;

    Poco::SharedPtr <UserLibrary> m_userLibrary;
    Poco::SharedPtr <DataBase> m_dataBase;

    const std::string NAME_TABLE = TABLES::Users;
};


#endif //MUSICBASEDATA_USER_H
