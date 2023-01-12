//
// Created by Вера on 10.12.2022.
//

#include "General/headers/DataBase.h"
#include "Objects/headers/Playlist.h"
#include "Objects/headers/Song.h"
#include "Objects/headers/SharedLibrary.h"

int x = 200;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Poco::SharedPtr<DataBase> dataBase = Poco::makeShared<DataBase>();
    try {
        dataBase->insertPerformer("performer", "Dora", "093567");
        dataBase->insertPerformer("performer2", "Serj Tankian", "26574");
        dataBase->insertUser("user", "user", "4994949");
        dataBase->insertUser("user2", "user2", "463542226", true);
        dataBase->insertGenre("cute rock");
        dataBase->insertGenre("rock");
        dataBase->insertGenre("pop");
        dataBase->insertGenre("indie");

        dataBase->insertAlbum("ДораДура", "Dora", "ssilka", true);
        dataBase->insertAlbum("SkyIsOver", "Serj Tankian", "ssilka", true);
        dataBase->insertAlbum("Elect The Dead", "Serj Tankian", "ssilka", true);
        dataBase->insertSong("Дура", "cute rock", "ДораДура", "ssilka", "Dora");
        dataBase->insertSong("SkyIsOver", "rock", "Elect The Dead", "ssilka2", "Serj Tankian");
        dataBase->insertSong("Elect The Dead", "rock", "Elect The Dead", "ssilka3", "Serj Tankian");
        dataBase->insertSong("Lie Lie Lie", "rock", "Elect The Dead", "ssilka4", "Serj Tankian");

//        dataBase->insertPlaylist("playlist1", "user", "ssilka1");
//
//        Playlist playlist("user", "urur", dataBase);
//        playlist.addSong("song1", "lll");
//        playlist.addSong("song2", "lll");
//        playlist.removeSong("song1", "lll");
//        playlist.setCoverArt("ssilka3");
//        playlist.setName("urur");
//
//        dataBase->insertPerformer("performer2", "rrr", "09356447");
//        Song song("song1", "lll", dataBase);
//        song.setName("rage");
//        song.setFeat("rrr");
//        song.setFeat("lll");
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.message();
    }

    SharedLibrary SL(dataBase);
    int choice{};
    while(choice != 4)
    {
        choice = 0;
        std::cout << "\n1. Общий каталог \n2. Войти \n3. Зарегистрироваться\n4. Выйти из приложения\n";
        std::cin >> choice;
        switch (choice)
        {
            case 1:
            {
                auto songs = SL.getAllSongs();
                std::cout << "\nпесни: ";
                for (auto song: songs)
                    std::cout << "\n название: " << song.getName() << "\n альбом: " << song.getAlbumName()
                              << "\n исполнитель: " << song.getPerformerName() << "\n";
                auto perf = SL.getAllPerformers();
                std::cout << "\nисполнители: \n";
                for (auto p: perf)
                    std::cout << p.getName() << "\n";
                auto albums = SL.getAllAlbums();
                std::cout << "\nальбомы: ";
                for (auto a: albums)
                    std::cout << "\n название: " << a.getName() << "\n исполнитель: " << a.getName() << "\n";
                break;
            }
            case 2:
            {
                std::string login{}, pass{};
                std::cout << "\n Введите логин\n";
                std::cin.ignore();
                std::getline(std::cin, login);
                std::cout << "\n Введите пароль\n";
                std::getline(std::cin, pass);
                if (dataBase->checkUserPass(login, pass))
                {
                    choice = 0;
                    while (choice != 3)
                    {
                        User user(dataBase->getUserIdByLogin(login), dataBase);
                        std::cout << "\n1. Общий каталог \n2. Свой каталог \n3. Выйти\n";
                        std::cin >> choice;
                        switch (choice)
                        {
                            case 1:
                            {
                                choice = 0;
                                while (choice != 4)
                                {
                                    choice = 0;
                                    std::cout << "\n1. Песни \n2. Исполнители \n3. Альбомы\n 4.Назад\n";
                                    std::cin >> choice;
                                    switch (choice)
                                    {
                                        case 1:
                                        {
                                            auto songs = SL.getAllSongs();
                                            std::cout << "\nпесни: \n";
                                            for (int i{}; i < songs.size(); ++i)
                                                std::cout << i << ". название: " << songs[i].getName() << " альбом: "
                                                          << songs[i].getAlbumName() << " исполнитель: "
                                                          << songs[i].getPerformerName() << "\n";

                                            choice = 0;
                                            while (choice != 2)
                                            {
                                                std::cout << "\n1. Добавить песню в свой каталог \n2. Назад\n";
                                                std::cin >> choice;
                                                switch (choice)
                                                {
                                                    case 1:
                                                        int x;
                                                        std::cout << "\nвведите номер песни\n";
                                                        std::cin >> x;
                                                        user.rateSong(dataBase->getSongId(songs[x].getName(),
                                                                                          songs[x].getPerformerName()),
                                                                      true);
                                                        break;
                                                }
                                            }
                                            break;
                                            choice = 0;
                                        }
                                        case 2:
                                        {
                                            auto perf = SL.getAllPerformers();
                                            std::cout << "\nисполнители: \n";
                                            for (int i{}; i < perf.size(); ++i)
                                                std::cout << i << ". " << perf[i].getName() << "\n";

                                            choice = 0;
                                            while (choice != 3)
                                            {
                                                std::cout << "\n1. Добавить исполнителя в свой каталог \n2. Перейти к исполнителю \n3. Назад\n";
                                                std::cin >> choice;
                                                switch (choice)
                                                {
                                                    case 1:
                                                    {
                                                        int x;
                                                        std::cout << "\nвведите номер исполнителя\n";
                                                        std::cin >> x;
                                                        user.ratePerformer(
                                                                dataBase->getPerformerIdByNickname(perf[x].getName()),
                                                                true);
                                                        break;
                                                    }
                                                    case 2:
                                                    {
                                                        int x;
                                                        std::cout << "\nвведите номер исполнителя\n";
                                                        std::cin >> x;
                                                        auto al = perf[x].getAlbums();
                                                        auto s = perf[x].getSongs();
                                                        std::cout << "\nпесни: ";
                                                        for (int i{}; i < s.size(); ++i)
                                                            std::cout << "\n название: " << s[i].getName()
                                                                      << " альбом: " << s[i].getAlbumName()
                                                                      << " исполнитель: " << s[i].getPerformerName()
                                                                      << "\n";
                                                        std::cout << "\naльбомы: ";
                                                        for (int i{}; i < al.size(); ++i)
                                                            std::cout << "\n название: " << al[i].getName()
                                                                      << "\n исполнитель: " << al[i].getName() << "\n";
                                                    }
                                                }
                                            }
                                            choice = 0;
                                            break;
                                        }
                                        case 3:
                                        {
                                            auto albums = SL.getAllAlbums();
                                            std::cout << "\naльбомы: \n";
                                            for (int i{}; i < albums.size(); ++i)
                                                std::cout << "\n" << i << " название: " << albums[i].getName()
                                                          << "\n исполнитель: " << albums[i].getName() << "\n";

                                            choice = 0;
                                            while (choice != 3)
                                            {
                                                std::cout << "\n1. Добавить альбом в свой каталог \n2. Перейти к альбому \n3. Назад\n";
                                                std::cin >> choice;
                                                switch (choice)
                                                {
                                                    case 1:
                                                    {
                                                        int x;
                                                        std::cout << "\nвведите номер альбома\n";
                                                        std::cin >> x;
                                                        user.rateAlbum(dataBase->getAlbumId(albums[x].getName(),
                                                                                            albums[x].getPerformerNickname()),
                                                                       true);
                                                        break;
                                                    }
                                                    case 2:
                                                    {
                                                        int x;
                                                        std::cout << "\nвведите номер альбома\n";
                                                        std::cin >> x;
                                                        auto s = albums[x].getSongs();
                                                        std::cout << "\nпесни: ";
                                                        for (int i{}; i < s.size(); ++i)
                                                            std::cout << i << ". название: " << s[i].getName()
                                                                      << " альбом: " << s[i].getAlbumName()
                                                                      << " исполнитель: " << s[i].getPerformerName()
                                                                      << "\n";
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                break;
                            }
                            case 2:
                            {
                                choice = 0;
                                while (choice != 5)
                                {
                                    choice = 0;
                                    std::cout << "\n1. Песни \n2. Исполнители \n3. Альбомы\n4. Плейлисты \n5.Назад\n";
                                    std::cin >> choice;
                                    switch (choice)
                                    {
                                        case 1:
                                        {
                                            auto songs = user.getUserLibrary()->getSongs();
                                            std::cout << "\nпесни: \n";
                                            for (int i{}; i < songs.size(); ++i)
                                                std::cout << i << ". название: " << songs[i].getName() << " альбом: "
                                                          << songs[i].getAlbumName() << " исполнитель: "
                                                          << songs[i].getPerformerName() << "\n";

                                            choice = 0;
                                            while (choice != 2)
                                            {
                                                std::cout << "\n1. Удалить песню из своего каталога \n2. Назад\n";
                                                std::cin >> choice;
                                                switch (choice)
                                                {
                                                    case 1:
                                                        int x;
                                                        std::cout << "\nвведите номер песни\n";
                                                        std::cin >> x;
                                                        user.rateSong(dataBase->getSongId(songs[x].getName(),
                                                                                          songs[x].getPerformerName()),
                                                                      false);
                                                        break;
                                                }
                                            }
                                            break;
                                            choice = 0;
                                        }
                                        case 2:
                                        {
                                            auto perf = user.getUserLibrary()->getPerformers();
                                            std::cout << "\nисполнители: \n";
                                            for (int i{}; i < perf.size(); ++i)
                                                std::cout << i << ". " << perf[i].getName() << "\n";

                                            choice = 0;
                                            while (choice != 3)
                                            {
                                                std::cout
                                                        << "\n1. Удалить исполнителя из своего каталога \n2. Перейти к исполнителю \n3. Назад\n";
                                                std::cin >> choice;
                                                switch (choice)
                                                {
                                                    case 1:
                                                    {
                                                        int x;
                                                        std::cout << "\nвведите номер исполнителя\n";
                                                        std::cin >> x;
                                                        user.ratePerformer(
                                                                dataBase->getPerformerIdByNickname(perf[x].getName()),
                                                                false);
                                                        break;
                                                    }
                                                    case 2:
                                                    {
                                                        int x;
                                                        std::cout << "\nвведите номер исполнителя\n";
                                                        std::cin >> x;
                                                        auto al = perf[x].getAlbums();
                                                        auto s = perf[x].getSongs();
                                                        std::cout << "\nпесни: \n";
                                                        for (int i{}; i < s.size(); ++i)
                                                            std::cout << "название: " << s[i].getName()
                                                                      << " альбом: " << s[i].getAlbumName()
                                                                      << "\n";
                                                        std::cout << "\naльбомы: ";
                                                        for (int i{}; i < al.size(); ++i)
                                                            std::cout << "\n название: " << al[i].getName()
                                                                      << "\n исполнитель: " << al[i].getName() << "\n";
                                                    }
                                                }
                                            }
                                            choice = 0;
                                            break;
                                        }
                                        case 3:
                                        {
                                            auto albums = user.getUserLibrary()->getAlbums();
                                            std::cout << "\naльбомы: \n";
                                            for (int i{}; i < albums.size(); ++i)
                                                std::cout << "\n" << i << " название: " << albums[i].getName()
                                                          << "\n исполнитель: " << albums[i].getPerformerNickname() << "\n";

                                            choice = 0;
                                            while (choice != 3)
                                            {
                                                std::cout
                                                        << "\n1. Удалить алтьбом из своего каталога \n2. Перейти к альбому \n3. Назад\n";
                                                std::cin >> choice;
                                                switch (choice)
                                                {
                                                    case 1:
                                                    {
                                                        int x;
                                                        std::cout << "\nвведите номер альбома\n";
                                                        std::cin >> x;
                                                        user.rateAlbum(dataBase->getAlbumId(albums[x].getName(),
                                                                                            albums[x].getPerformerNickname()),
                                                                       false);
                                                        break;
                                                    }
                                                    case 2:
                                                    {
                                                        int x;
                                                        std::cout << "\nвведите номер альбома\n";
                                                        std::cin >> x;
                                                        auto s = albums[x].getSongs();
                                                        std::cout << "\nпесни: ";
                                                        for (int i{}; i < s.size(); ++i)
                                                            std::cout << i << ". название: " << s[i].getName()
                                                                      << " альбом: " << s[i].getAlbumName()
                                                                      << " исполнитель: " << s[i].getPerformerName()
                                                                      << "\n";
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        case 4:
                                        {
                                            choice = 0;
                                            while (choice != 3)
                                            {
                                                auto pl = user.getUserLibrary()->getOwnPlaylists();
                                                std::cout << "\nплейлисты: \n";
                                                for (int i{}; i < pl.size(); ++i)
                                                    std::cout << "\n" << i << " название: " << pl[i].getName();

                                                std::cout
                                                        << "\n1. Создать плейлист \n2. Перейти к плейлисту \n3. Назад\n";
                                                std::cin >> choice;
                                                switch (choice)
                                                {
                                                    case 1:
                                                    {
                                                        std::string name{}; int b;
                                                        std::cout << "\nвведите имя плейлиста\n";
                                                        std::cin.ignore();
                                                        std::cin >> name;
                                                        std::cout << "\n1. публичный 2. закрытый\n";
                                                        std::cin >> b;
                                                        dataBase->insertPlaylist(name, user.getNick(), "ssilka"+std::to_string(x++),
                                                                                 b == 1);
                                                        break;
                                                    }
                                                    case 2:
                                                    {
                                                        int x;
                                                        std::cout << "\nвведите номер плейлиста\n";
                                                        std::cin >> x;
                                                        auto s = pl[x].getSongs();
                                                        std::cout << "\nпесни: ";
                                                        for (int i{}; i < s.size(); ++i)
                                                            std::cout << i << ". название: " << s[i].getName()
                                                                      << " альбом: " << s[i].getAlbumName()
                                                                      << " исполнитель: " << s[i].getPerformerName()
                                                                      << "\n";
                                                        choice = 0;
                                                        while (choice != 3)
                                                        {
                                                            std::cout << "\n1. Добавить песню \n2. Удалить песню \n3. Назад\n";
                                                            std::cin >> choice;
                                                            switch (choice)
                                                            {
                                                                case 1:
                                                                {
                                                                    auto songs = user.getUserLibrary()->getSongs();
                                                                    std::cout << "\nпесни из вашего каталога: \n";
                                                                    for (int i{}; i < songs.size(); ++i)
                                                                        std::cout << i << ". название: " << songs[i].getName() << " альбом: "
                                                                                  << songs[i].getAlbumName() << " исполнитель: "
                                                                                  << songs[i].getPerformerName() << "\n";
                                                                    int x2;
                                                                    std::cout << "\nвведите номер песни из каталога\n";
                                                                    std::cin >> x2;
                                                                    pl[x].addSong(songs[x2].getName(), songs[x2].getPerformerName());
                                                                    break;
                                                                }
                                                                case 2:
                                                                {
                                                                    int x2;
                                                                    std::cout << "\nвведите номер песни из плейлиста\n";
                                                                    std::cin >> x2;
                                                                    pl[x].removeSong(s[x2].getName(), s[x2].getPerformerName());
                                                                    break;
                                                                }
                                                            }
                                                        }
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
                else
                    std::cout << "Неверный логин или пароль\n";
                break;
            }
            case 3:
            {
                std::string login{}, pass{}; std::string nickname{};
                std::cout << "\n Введите логин\n";
                std::cin.ignore();
                std::getline(std::cin, login);
                std::cout << "\n Введите пароль\n";
                std::getline(std::cin, pass);
                std::cout << "\n Введите никнейм\n";
                std::getline(std::cin, nickname);

                if (dataBase->getUserIdByLogin(login) != 0)
                {
                    std::cout << "\n Пользователь с таким логином уже существует";
                    break;
                }
                if (dataBase->getUserIdByNickname(nickname) != 0)
                {
                    std::cout << "\n Пользователь с таким именем уже существует";
                    break;
                }
                dataBase->insertUser(login, nickname, pass);
            }
        }
    }

    return 0;
}