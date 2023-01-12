//
// Created by Вера on 16.12.2022.
//

#ifndef MUSICBASEDATA_DBWORKER_H
#define MUSICBASEDATA_DBWORKER_H

#include "Poco/Data/Session.h"
#include "Poco/Data/PostgreSQL/Connector.h"
#include "Poco/SharedPtr.h"
#include "Poco/Timestamp.h"

using namespace Poco::Data::Keywords;

class DBWorker
{
public:
    DBWorker(Poco::SharedPtr<Poco::Data::Session> session);
    DBWorker();
    virtual ~DBWorker();

    template<typename T>
    void selectById(std::string nameParam, std::string nameTable, int id, T &container);

    template<typename T>
    void select(std::string nameParam, std::string nameTable, std::string nameParamForSearch, std::string value, T &container);

    template<typename T>
    void select(std::string nameParam, std::string nameTable, std::string nameParamForSearch1, std::string value,
                          std::string nameParamForSearch2, std::string value2, T &container);

    template<typename T>
    bool checkValue(std::string nameParam, std::string nameTable, std::string nameParamForSearch, std::string value, const T& compareValue);

    template<typename T>
    bool checkValueById(std::string nameParam, std::string nameTable, int id, const T& compareValue);

    virtual void update(std::string nameTable, std::string nameParam, std::string value, int id);
    virtual void update(std::string nameTable, std::string nameParam, std::string value, std::string nameId, int id, std::string nameId2, int id2);

    virtual void markForDeletion(std::string nameTable, std::string nameParam, int id);
    virtual void markForDeletion(std::string nameTable, std::string nameParam, std::string nameId, int id, std::string nameId2, int id2);

    virtual void remove(std::string nameTable, std::string nameParam, int id);
    virtual void remove(std::string nameTable, std::string nameId, int id, std::string nameId2, int id2);
protected:
    Poco::SharedPtr<Poco::Data::Session> m_session;
};

template<typename T>
void DBWorker::selectById(std::string nameParam, std::string nameTable, int id, T &container)
{
    select<T>(nameParam, nameTable, "id", std::to_string(id), container);
}

template<typename T>
void DBWorker::select(std::string nameParam, std::string nameTable, std::string nameParamForSearch, std::string value, T &container)
{
    Poco::Data::Statement get(*m_session);
    get << Poco::format(R"(SELECT %s FROM %s WHERE %s='%s')", nameParam, nameTable, nameParamForSearch, value),
            into(container);
    get.execute();
}

template<typename T>
void DBWorker::select(std::string nameParam, std::string nameTable, std::string nameParamForSearch1, std::string value,
                      std::string nameParamForSearch2, std::string value2, T &container)
{
    Poco::Data::Statement get(*m_session);
    get << Poco::format(R"(SELECT %s FROM %s WHERE %s='%s' AND %s = '%s')", nameParam, nameTable, nameParamForSearch1, value, nameParamForSearch2, value2),
            into(container);
    get.execute();
}

template<typename T>
bool DBWorker::checkValue(std::string nameParam, std::string nameTable, std::string nameParamForSearch, std::string paramValue,
                          const T& compareValue)
{
    T realVal;
    select<T>(nameParam, nameTable, nameParamForSearch, paramValue, realVal);
    return realVal==compareValue;
}


template<typename T>
bool DBWorker::checkValueById(std::string nameParam, std::string nameTable, int id, const T &compareValue)
{
    T realVal;
    selectById<T>(nameParam, nameTable, id, realVal);
    return realVal==compareValue;
}

#endif //MUSICBASEDATA_DBWORKER_H
