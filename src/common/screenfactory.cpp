#include "screenfactory.h"

using namespace screens;

ScreensFactory::ScreensFactory(QString start_tag) {
    m_startTag = start_tag;
}

BaseFragment *ScreensFactory::create(QString tag) {
    qDebug("ScreensFactory create");
    if (tag == SPLASH_TAG) {
        return new SplashFragment;
    }
    else if (tag == START_TAG) {
        return new StartFragment;
    }
    else if (tag == LOGIN_TAG) {
        return new LoginFragment;
    }
    else if (tag == REGISTRATION_TAG) {
        return new RegistrFragment;
    }
    else if (tag == START_USER_TAG) {
        return new UserStartFragment;
    }
    else if (tag == START_PERF_TAG) {
        return new PerformerStartFragment;
    }
    else if (tag == CATALOG_TAG) {
        return new CatalogFragment;
    }
    else if (tag == CATEGORY_TAG) {
        return new CategoryFragment;
    }
    else if (tag == SEARCH_TAG) {
        return new SearchFragment;
    }
    else if (tag == PLAYLIST_TAG) {
        return new PlaylistFragment;
    }
    else if (tag == USER_TAG) {
        return new UserFragment;
    }
    else if (tag == ALBUM_TAG) {
        return new AlbumFragment;
    }
    else if (tag == PERFORMER_TAG) {
        return new PerformerFragment;
    }
    else if (tag == USER_FAVOURITES_TAG) {
        return new UserFavourites;
    }
    else if (tag == USER_PLAYLISTS_TAG) {
        return new UserPlaylists;
    }
    else if (tag == USER_LIBRARY_TAG) {
        return new UserLibraryFragment;
    }
    else if (tag == CREATE_PLAYLIST_TAG) {
        return new CreatePlaylistFragment;
    }
    else if (tag == GENRE_TAG) {
        return new GenreFragment;
    }
    else if (tag == PERFTOOLS_TAG) {
        return new PerformerToolsFragment;
    }
    else if (tag == CREATE_ALBUM_TAG) {
        return new CreateAlbumFragment;
    }
    return nullptr;
}

QString ScreensFactory::createStart() {
    return m_startTag; // идентификатор стартового экрана
}