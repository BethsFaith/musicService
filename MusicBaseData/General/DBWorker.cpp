//
// Created by Вера on 16.12.2022.
//

#include "headers/DBWorker.h"

DBWorker::DBWorker(Poco::SharedPtr<Poco::Data::Session> session) : m_session(session)
{}

DBWorker::DBWorker()
{}

DBWorker::~DBWorker()
{

}

void DBWorker::update(std::string nameTable, std::string nameParam, std::string value, int id)
{
    Poco::Data::Statement update(*m_session);
    update << Poco::format(R"(UPDATE %s SET %s='%s' WHERE id ='%d')", nameTable, nameParam, value, id);
    update.execute();
}

void DBWorker::update(std::string nameTable, std::string nameParam, std::string value, std::string nameId, int id, std::string nameId2, int id2)
{
    Poco::Data::Statement update(*m_session);
    update <<  Poco::format(R"(UPDATE %s SET %s='%s' WHERE %s='%d' AND %s = '%d')", nameTable, nameParam, value, nameId, id, nameId2, id2);
    update.execute();
}

void DBWorker::markForDeletion(std::string nameTable, std::string nameParam, int id)
{
    Poco::Data::Statement update(*m_session);
    update <<  Poco::format(R"(UPDATE %s SET %s = null WHERE id='%d')", nameTable, nameParam, id);
    update.execute();
}

void DBWorker::markForDeletion(std::string nameTable, std::string nameParam, std::string nameId, int id, std::string nameId2,
                          int id2)
{
    Poco::Data::Statement update(*m_session);
    update <<  Poco::format(R"(UPDATE %s SET %s = null WHERE %s='%d' AND %s='%d')", nameTable, nameParam, nameId, id, nameId2, id2);
    update.execute();
}

void DBWorker::remove(std::string nameTable, std::string nameParam, int id)
{
    Poco::Data::Statement remove(*m_session);
    remove <<  Poco::format(R"(DELETE FROM %s WHERE %s='%d')", nameTable, nameParam, id);
    remove.execute();
}

void DBWorker::remove(std::string nameTable, std::string nameId, int id, std::string nameId2, int id2)
{
    Poco::Data::Statement remove(*m_session);
    remove <<  Poco::format(R"(DELETE FROM %s WHERE %s='%d' AND %s='%d')", nameTable, nameId, id, nameId2, id2);
    remove.execute();
}
