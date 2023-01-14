#ifndef DATABASEMODEL_H
#define DATABASEMODEL_H

#include "../base/basemodel.h"
#include "../../MusicBaseData/General/headers/DataBase.h"

class DataBaseModel: public BaseModel
{
public:
    DataBaseModel(Poco::SharedPtr <DataBase> db);

    Poco::SharedPtr <DataBase> getDb();

private:
    Poco::SharedPtr <DataBase> m_db;
};

#endif // DATABASEMODEL_H
