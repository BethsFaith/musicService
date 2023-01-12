//
// Created by Вера on 17.12.2022.
//

#ifndef MUSICBASEDATA_SHAREDLIBRARY_H
#define MUSICBASEDATA_SHAREDLIBRARY_H

#include "../../General/headers/DataBase.h"
#include "Song.h"
#include "Album.h"
#include "Playlist.h"
#include "Category.h"
#include "../../Persons/headers/Performer.h"
#include "../../Persons/headers/User.h"
#include "genre.h"

class SharedLibrary : DBWorker
{
public:
    SharedLibrary(Poco::SharedPtr<DataBase> dataBase);

    std::vector<Song> getAllSongs();
    std::vector<Album> getAllAlbums();
    std::vector<Performer> getAllPerformers();
    std::vector<Playlist> getAllPlaylists();
    std::vector<User> getAllUsers();
    std::vector<Category> getAllCategories();

//    std::vector<Song> getSongsByGenre(int genreId);
    std::vector<Genre> getAllGenres();
    const Poco::SharedPtr<DataBase> &dataBase() const;
    void setDataBase(const Poco::SharedPtr<DataBase> &newDataBase);

  private:
    Poco::SharedPtr<DataBase> m_dataBase;
};


#endif //MUSICBASEDATA_SHAREDLIBRARY_H
