cmake_minimum_required(VERSION 3.23)
project(MusicBaseData)

project(MusicBaseData
        VERSION 1.0.0
        DESCRIPTION "BlockSpace C++ library built with CMake"
        LANGUAGES CXX)

find_package(Poco REQUIRED Foundation Data DataPostgreSQL)
find_package(PostgreSQL REQUIRED)

set(SOURCE_FILES src/General/DataBase.cpp src/Objects/Playlist.cpp src/General/DBWorker.cpp src/Objects/Song.cpp src/Persons/Performer.cpp src/Objects/Album.cpp src/Persons/User.cpp src/Objects/UserLibrary.cpp src/Objects/SharedLibrary.cpp src/Objects/Category.cpp src/Objects/Genre.cpp)
set(HEADER_FILES src/General/headers/DataBase.h src/Objects/headers/Playlist.h src/General/headers/DBWorker.h src/Objects/headers/Song.h src/Persons/headers/Performer.h src/Objects/headers/Album.h src/Persons/headers/User.h src/Objects/headers/UserLibrary.h src/Objects/headers/SharedLibrary.h src/Objects/headers/Category.h src/Objects/headers/Genre.h)

add_library(MusicBaseData STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(MusicBaseData PUBLIC PostgreSQL::PostgreSQL Poco::Foundation Poco::Data Poco::DataPostgreSQL)
