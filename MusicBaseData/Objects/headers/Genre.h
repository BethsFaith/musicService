#ifndef GENRE_H
#define GENRE_H

#include "../../General/headers/DBWorker.h"
#include "../../General/headers/DataBase.h"
#include "Song.h"

class Genre: public DBWorker
{
public:
    Genre(int id, Poco::SharedPtr <DataBase> db);

    const std::string &name() const;

    void setName(const std::string &newName);

    const std::string &cover_art() const;

    void setCover_art(const std::string &newCover_art);

    std::vector <Song> getSongs();

    Poco::SharedPtr <DataBase> getDB();

private:
    int m_id;
    std::string m_name;
    std::string m_coverArt;

    Poco::SharedPtr <DataBase> m_dataBase;

    const std::string NAME_TABLE = TABLES::Genres;
};

#endif // GENRE_H
