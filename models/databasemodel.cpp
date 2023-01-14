#include "databasemodel.h"

DataBaseModel::DataBaseModel(Poco::SharedPtr <DataBase> db) : m_db{db} {}

Poco::SharedPtr <DataBase> DataBaseModel::getDb() {
    return m_db;
}
