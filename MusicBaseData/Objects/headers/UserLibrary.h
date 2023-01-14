//
// Created by Вера on 17.12.2022.
//

#ifndef MUSICBASEDATA_USERLIBRARY_H
#define MUSICBASEDATA_USERLIBRARY_H

#include "../../General/headers/DataBase.h"
#include "Song.h"
#include "Album.h"
#include "Playlist.h"
#include "../../Persons/headers/Performer.h"

class UserLibrary: DBWorker
{
public:
    UserLibrary(int userId, Poco::SharedPtr <DataBase> dataBase);

    std::vector <Song> getSongs();

    std::vector <Album> getAlbums();

    std::vector <Performer> getPerformers();

    std::vector <Playlist> getPlaylists();

    std::vector <Playlist> getOwnPlaylists();

private:
    int m_userId;
    Poco::SharedPtr <DataBase> m_dataBase;
};


#endif //MUSICBASEDATA_USERLIBRARY_H
