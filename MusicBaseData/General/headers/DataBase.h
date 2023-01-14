//
// Created by Вера on 10.12.2022.
//

#ifndef MUSICBASEDATA_DATABASE_H
#define MUSICBASEDATA_DATABASE_H

#include "Poco/Data/Session.h"
#include "Poco/Data/PostgreSQL/Connector.h"
#include "Poco/SharedPtr.h"
#include "Poco/Timestamp.h"
#include <utility>
#include <vector>
#include <iostream>
#include "DBWorker.h"

using namespace Poco::Data::Keywords;

namespace TABLES
{
    static const std::string Songs{"songs"};
    static const std::string Performers{"performers"};
    static const std::string Users{"users"};
    static const std::string Playlists{"playlists"};
    static const std::string B_Song_Playlist{"bond_songsplaylists"};
    static const std::string B_Category_Playlist{"bond_categoriesplaylists"};
    static const std::string Genres{"genres"};
    static const std::string Categories{"Categories"};
    static const std::string Feats{"feats"};
    static const std::string Albums{"albums"};
    static const std::string LikedSongs{"likedSongs"};
    static const std::string LikedPerf{"likedPerformers"};
    static const std::string LikedPlaylists{"likedPlaylists"};
    static const std::string LikedAlbums{"likedAlbums"};
}

class DataBase: public DBWorker
{
public:
    DataBase();

    void insertUser(std::string login, std::string nickname, std::string pass, bool isModerator = false);

    void insertPerformer(std::string login, std::string nickname, std::string pass);

    void insertGenre(std::string name);

    void insertSong(std::string name, std::string genreName, std::string albumName,
                    std::string performerName);

    void insertAlbum(std::string name, const std::string &performerName, std::string coverArt, bool isPublic = false);

    void insertPlaylist(std::string name, const std::string &userName, std::string coverArt, bool isPublic = false);

    void insertCategory(std::string name, std::string picture);

    int getUserIdByNickname(std::string nickName);

    int getUserIdByLogin(std::string login);

    int getPerformerIdByNickname(std::string name);

    int getPerformerIdByLogin(std::string name);

    int getGenreId(std::string name);

    int getAlbumId(std::string name, const std::string &performerName);

    int getSongId(std::string name, const std::string &performerName);

    int getPlaylistId(std::string name, const std::string &userName);

    int getCategoryId(std::string name);

    void deleteSong(int songId);

    void deleteAlbum(int albumId);

    void deleteUser(int userId);

    void deletePerformer(int userId);

    void deleteCategory(int categoryId);

    void deletePlaylist(int playlistId);

    bool checkUserPass(std::string login, std::string pass);

    bool checkPerformerPass(std::string login, std::string pass);

    std::vector <std::string> getSongsByPerformer(std::string performerName);

    Poco::SharedPtr <Poco::Data::Session> getSession();
};

#endif //MUSICBASEDATA_DATABASE_H
