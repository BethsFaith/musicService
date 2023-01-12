cmake_minimum_required(VERSION 3.23)
project(MusicBaseData)
#
#set(CMAKE_CXX_STANDARD 20)
#find_package(Poco REQUIRED Foundation Data DataPostgreSQL)
#find_package(PostgreSQL REQUIRED)
#    add_library(MusicBaseData General/DataBase.cpp General/headers/DataBase.h Objects/Playlist.cpp Objects/headers/Playlist.h General/DBWorker.cpp General/headers/DBWorker.h Objects/Song.cpp Objects/headers/Song.h Persons/Performer.cpp Persons/headers/Performer.h Objects/Album.cpp Objects/headers/Album.h Persons/User.cpp Persons/headers/User.h Objects/UserLibrary.cpp Objects/headers/UserLibrary.h Objects/SharedLibrary.cpp Objects/headers/SharedLibrary.h Objects/Category.cpp Objects/headers/Category.h)
#include_directories(Persons/headers/ Objects/headers/ General/headers/)
#target_link_libraries(MusicBaseData PRIVATE PostgreSQL::PostgreSQL Poco::Foundation Poco::Data Poco::DataPostgreSQL)
#
#add_executable(Example example.cpp)
#target_link_libraries(Example MusicBaseData)

project(MusicBaseData
        VERSION 1.0.0
        DESCRIPTION "BlockSpace C++ library built with CMake"
        LANGUAGES CXX)

#set(CMAKE_PREFIX_PATH D:/QT/5.12.12/mingw73_64)

find_package(Poco REQUIRED Foundation Data DataPostgreSQL)
find_package(PostgreSQL REQUIRED)
#    add_library(MusicBaseData General/DataBase.cpp General/headers/DataBase.h Objects/Playlist.cpp Objects/headers/Playlist.h General/DBWorker.cpp General/headers/DBWorker.h Objects/Song.cpp Objects/headers/Song.h Persons/Performer.cpp Persons/headers/Performer.h Objects/Album.cpp Objects/headers/Album.h Persons/User.cpp Persons/headers/User.h Objects/UserLibrary.cpp Objects/headers/UserLibrary.h Objects/SharedLibrary.cpp Objects/headers/SharedLibrary.h Objects/Category.cpp Objects/headers/Category.h)
#include_directories(Persons/headers/ Objects/headers/ General/headers/)

#add_library(MusicBaseData)
#add_library(MusicBaseData::MusicBaseData ALIAS MusicBaseData)

set(SOURCE_FILES General/DataBase.cpp Objects/Playlist.cpp General/DBWorker.cpp Objects/Song.cpp Persons/Performer.cpp Objects/Album.cpp Persons/User.cpp Objects/UserLibrary.cpp Objects/SharedLibrary.cpp Objects/Category.cpp Objects/genre.cpp)
set(HEADER_FILES General/headers/DataBase.h Objects/headers/Playlist.h General/headers/DBWorker.h Objects/headers/Song.h Persons/headers/Performer.h Objects/headers/Album.h Persons/headers/User.h Objects/headers/UserLibrary.h Objects/headers/SharedLibrary.h Objects/headers/Category.h Objects/headers/genre.h)

# We declare the project as a static library and add all the source code files to it.
add_library(MusicBaseData STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(MusicBaseData PUBLIC PostgreSQL::PostgreSQL Poco::Foundation Poco::Data Poco::DataPostgreSQL)

#target_sources(MusicBaseData PRIVATE General/DataBase.cpp Objects/Playlist.cpp General/DBWorker.cpp Objects/Song.cpp Persons/Performer.cpp Objects/Album.cpp Persons/User.cpp Objects/UserLibrary.cpp Objects/SharedLibrary.cpp Objects/Category.cpp)
#target_sources(MusicBaseData PUBLIC General/headers/DataBase.h Objects/headers/Playlist.h General/headers/DBWorker.h Objects/headers/Song.h Persons/headers/Performer.h Objects/headers/Album.h Persons/headers/User.h Objects/headers/UserLibrary.h Objects/headers/SharedLibrary.h Objects/headers/Category.h)
#
#string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
#        is_top_level)
