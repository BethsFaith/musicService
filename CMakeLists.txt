cmake_minimum_required(VERSION 3.24)
project(MusicService)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        )

find_package(Poco REQUIRED Foundation Data DataPostgreSQL)
find_package(PostgreSQL REQUIRED)

add_subdirectory("./MusicBaseData")
add_executable(MusicService src/main.cpp
        src/base/basefragment.h src/base/basefragment.cpp src/base/basefragment.ui
        src/fragments/startfragment.h src/fragments/startfragment.cpp src/fragments/startfragment.ui
        src/fragments/loginfragment.h src/fragments/loginfragment.cpp src/fragments/loginfragment.ui
        src/fragments/registrfragment.h src/fragments/registrfragment.cpp src/fragments/registrfragment.ui
        src/base/basescreensfactory.h
        src/common/screenfactory.h src/common/screenfactory.cpp
        src/fragments/splashfragment.h src/fragments/splashfragment.cpp src/fragments/splashfragment.ui
        src/base/basemodel.h
        src/common/navigator.h src/common/navigator.cpp
        src/common/mainwindow.h src/common/mainwindow.cpp
        src/models/usermodel.h src/models/usermodel.cpp
        src/models/performermodel.h src/models/performermodel.cpp
        src/models/databasemodel.h src/models/databasemodel.cpp
        src/fragments/userstartfragment.h src/fragments/userstartfragment.cpp src/fragments/userstartfragment.ui
        src/fragments/performerstartfragment.h src/fragments/performerstartfragment.cpp src/fragments/performerstartfragment.ui
        src/fragments/categoryfragment.h src/fragments/categoryfragment.cpp src/fragments/categoryfragment.ui
        src/base/basepicturepb.h src/base/basepicturepb.cpp src/base/basepicturepb.ui
        src/buttons/categorypb.h src/buttons/categorypb.cpp
        src/fragments/catalogfragment.h src/fragments/catalogfragment.cpp src/fragments/catalogfragment.ui
        src/buttons/playlistpb.h src/buttons/playlistpb.cpp
        src/buttons/genrepb.h src/buttons/genrepb.cpp
        src/buttons/albumpb.h src/buttons/albumpb.cpp
        src/fragments/searchfragment.h src/fragments/searchfragment.cpp src/fragments/searchfragment.ui
        src/fragments/playlistfragment.h src/fragments/playlistfragment.cpp src/fragments/playlistfragment.ui
        src/fragments/performerfragment.h src/fragments/performerfragment.cpp src/fragments/performerfragment.ui
        src/fragments/albumfragment.h src/fragments/albumfragment.cpp src/fragments/albumfragment.ui
        src/fragments/userfragment.h src/fragments/userfragment.cpp src/fragments/userfragment.ui
        src/buttons/songpb.h src/buttons/songpb.cpp src/buttons/songpb.ui
        src/fragments/userlibraryfragment.h src/fragments/userlibraryfragment.cpp src/fragments/userlibraryfragment.ui
        src/fragments/userplaylists.h src/fragments/userplaylists.cpp src/fragments/userplaylists.ui
        src/fragments/userfavourites.h src/fragments/userfavourites.cpp src/fragments/userfavourites.ui
        src/fragments/createplaylistfragment.h src/fragments/createplaylistfragment.cpp src/fragments/createplaylistfragment.ui
        src/forms/playlistsform.h src/forms/playlistsform.cpp src/forms/playlistsform.ui
        src/actions/addsongtoplaylist.h src/actions/addsongtoplaylist.cpp
        src/actions/deletesongfromplaylist.h src/actions/deletesongfromplaylist.cpp
        src/fragments/genrefragment.h src/fragments/genrefragment.cpp src/fragments/genrefragment.ui
        src/fragments/performertoolsfragment.h src/fragments/performertoolsfragment.cpp src/fragments/performertoolsfragment.ui
        src/fragments/createalbumfragment.h src/fragments/createalbumfragment.cpp src/fragments/createalbumfragment.ui
        src/actions/deletesongfromalbum.h src/actions/deletesongfromalbum.cpp
        )
target_link_libraries(MusicService
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
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
