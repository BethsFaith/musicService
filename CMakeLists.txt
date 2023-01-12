cmake_minimum_required(VERSION 3.24)
project(MusicService)

set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_AUTOUIC_SEARCH_PATHS "D:\\studentsStuff\\Session\\3_course\\MusicService\\common" "D:\\studentsStuff\\Session\\3_course\\MusicService\\buttons" "D:\\studentsStuff\\Session\\3_course\\MusicService\\fragments" "D:\\studentsStuff\\Session\\3_course\\MusicService\\models")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        )

find_package(PostgreSQL REQUIRED)
find_package(Poco REQUIRED Foundation Data DataPostgreSQL)

#set(CMAKE_PREFIX_PATH D:/QT/5.12.12/mingw73_64)

add_subdirectory("./MusicBaseData")
add_executable(MusicService main.cpp
        base/basefragment.h base/basefragment.cpp base/basefragment.ui
        fragments/startfragment.h fragments/startfragment.cpp fragments/startfragment.ui
        fragments/loginfragment.h fragments/loginfragment.cpp fragments/loginfragment.ui
        fragments/registrfragment.h fragments/registrfragment.cpp fragments/registrfragment.ui
        base/basescreensfactory.h base/basescreensfactory.cpp
        common/screenfactory.h common/screenfactory.cpp
        fragments/splashfragment.h fragments/splashfragment.cpp fragments/splashfragment.ui
        base/basemodel.h base/basemodel.cpp
        common/navigator.h common/navigator.cpp
        common/mainwindow.h common/mainwindow.cpp
        stylecontainer.h stylecontainer.cpp
        models/usermodel.h models/usermodel.cpp
        models/performermodel.h models/performermodel.cpp
        models/databasemodel.h models/databasemodel.cpp
        fragments/userstartfragment.h fragments/userstartfragment.cpp fragments/userstartfragment.ui
        fragments/performerstartfragment.h fragments/performerstartfragment.cpp fragments/performerstartfragment.ui
        fragments/categoryfragment.h fragments/categoryfragment.cpp fragments/categoryfragment.ui
        models/categorymodel.h models/categorymodel.cpp
        buttons/categorypb.h buttons/categorypb.cpp buttons/categorypb.ui
        fragments/catalogfragment.h fragments/catalogfragment.cpp fragments/catalogfragment.ui
        buttons/playlistpb.h buttons/playlistpb.cpp buttons/playlistpb.ui
        fragments/searchfragment.h fragments/searchfragment.cpp fragments/searchfragment.ui
        fragments/playlistfragment.h fragments/playlistfragment.cpp fragments/playlistfragment.ui
        fragments/performerfragment.h fragments/performerfragment.cpp fragments/performerfragment.ui
        fragments/songfragment.h fragments/songfragment.cpp fragments/songfragment.ui
        fragments/albumfragment.h fragments/albumfragment.cpp fragments/albumfragment.ui
        fragments/userfragment.h fragments/userfragment.cpp fragments/userfragment.ui
        models/playlistmodel.h models/playlistmodel.cpp
        models/albummodel.h models/albummodel.cpp
        models/songmodel.h models/songmodel.cpp
        buttons/songpb.h buttons/songpb.cpp buttons/songpb.ui
        fragments/userlibraryfragment.h  fragments/userlibraryfragment.cpp  fragments/userlibraryfragment.ui
        fragments/userplaylists.h fragments/userplaylists.cpp fragments/userplaylists.ui
        fragments/userfavourites.h fragments/userfavourites.cpp fragments/userfavourites.ui
        fragments/createplaylistfragment.h fragments/createplaylistfragment.cpp fragments/createplaylistfragment.ui
        forms/playlistsform.h  forms/playlistsform.cpp  forms/playlistsform.ui
        actions/addsongtoplaylist.h actions/addsongtoplaylist.cpp
        actions/deletesongfromplaylist.h actions/deletesongfromplaylist.cpp
        fragments/genrefragment.h fragments/genrefragment.cpp fragments/genrefragment.ui
        fragments/performertoolsfragment.h fragments/performertoolsfragment.cpp fragments/performertoolsfragment.ui
        )
target_link_libraries(MusicService
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        #PostgreSQL::PostgreSQL Poco::Foundation Poco::Data Poco::DataPostgreSQL
        MusicBaseData
        )

    if (WIN32)
        set(DEBUG_SUFFIX)
        if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
            set(DEBUG_SUFFIX "d")
        endif ()
        set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
                set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            endif ()
        endif ()
        if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        endif ()
        foreach (QT_LIB Core Gui Widgets)
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
        endforeach (QT_LIB)
    endif ()
