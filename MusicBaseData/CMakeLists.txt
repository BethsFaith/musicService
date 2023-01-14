cmake_minimum_required(VERSION 3.23)
project(MusicBaseData)

project(MusicBaseData
        VERSION 1.0.0
        DESCRIPTION "BlockSpace C++ library built with CMake"
        LANGUAGES CXX)

find_package(Poco REQUIRED Foundation Data DataPostgreSQL)
find_package(PostgreSQL REQUIRED)

set(SOURCE_FILES General/DataBase.cpp Objects/Playlist.cpp General/DBWorker.cpp Objects/Song.cpp Persons/Performer.cpp Objects/Album.cpp Persons/User.cpp Objects/UserLibrary.cpp Objects/SharedLibrary.cpp Objects/Category.cpp Objects/Genre.cpp)
set(HEADER_FILES General/headers/DataBase.h Objects/headers/Playlist.h General/headers/DBWorker.h Objects/headers/Song.h Persons/headers/Performer.h Objects/headers/Album.h Persons/headers/User.h Objects/headers/UserLibrary.h Objects/headers/SharedLibrary.h Objects/headers/Category.h Objects/headers/Genre.h)

add_library(MusicBaseData STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(MusicBaseData PUBLIC PostgreSQL::PostgreSQL Poco::Foundation Poco::Data Poco::DataPostgreSQL)
