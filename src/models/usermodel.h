#ifndef USERMODULE_H
#define USERMODULE_H

#include "../base/basemodel.h"
#include "../../MusicBaseData/Persons/headers/User.h"

class UserModel: public BaseModel
{
public:
    UserModel(Poco::SharedPtr <User> user);

    void addSongToPlaylist(Poco::SharedPtr <Playlist> playlist, Poco::SharedPtr <Playlist> song);

    void addSongToPlaylist(std::string namePlaylist, std::string nameSong);

    Poco::SharedPtr <User> m_userBase;
};

#endif // USERMODULE_H
