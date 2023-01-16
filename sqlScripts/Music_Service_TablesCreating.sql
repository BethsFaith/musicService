CREATE TABLE Users
(
	Id SERIAL PRIMARY KEY,
	Login CHARACTER VARYING(30) UNIQUE NOT NULL,
	Nickname CHARACTER VARYING(20) UNIQUE NOT NULL,
	Password CHARACTER VARYING(30) NOT NULL,
	Is_Moderator BOOLEAN
);

CREATE TABLE Performers
(
	Id SERIAL PRIMARY KEY,
	Login CHARACTER VARYING(30) UNIQUE,
	Password CHARACTER VARYING(30) NOT NULL,
	Nickname CHARACTER VARYING(20) UNIQUE NOT NULL
);

CREATE TABLE Albums
(
	Id SERIAL PRIMARY KEY,
	Name CHARACTER VARYING(30) NOT NULL,
	Performer_Id INTEGER REFERENCES Performers (Id) ON DELETE CASCADE NOT NULL,
	CoverArt TEXT NOT NULL,
	Date TIMESTAMP NOT NULL,
	IsPublic BOOLEAN NOT NULL,
	UNIQUE(Name, Performer_Id)
);

CREATE TABLE Playlists
(
	Id SERIAL PRIMARY KEY,
	Name CHARACTER VARYING(30) NOT NULL,
	User_Id INTEGER REFERENCES Users (Id) ON DELETE CASCADE,
	CoverArt TEXT,
	Date TIMESTAMP NOT NULL,
	IsPublic BOOLEAN NOT NULL,
	UNIQUE(Name, User_Id)
);

CREATE TABLE Genres
(
	Id SERIAL PRIMARY KEY,
	Name CHARACTER VARYING(30) UNIQUE NOT NULL,
	CoverArt TEXT
);

CREATE TABLE Songs
(
	Id SERIAL PRIMARY KEY,
	Name CHARACTER VARYING(30) NOT NULL,
	Performer_Id INTEGER REFERENCES Performers (Id) NOT NULL,
	Album_Id INTEGER REFERENCES Albums (Id) ON DELETE CASCADE NOT NULL,
	Genre_Id INTEGER REFERENCES Genres (Id) ON DELETE SET NULL,
	UNIQUE(Name, Performer_Id)
);

CREATE TABLE Categories
(
	Id SERIAL PRIMARY KEY,
	Name CHARACTER VARYING(30) UNIQUE NOT NULL,
	CoverArt TEXT
);

CREATE TABLE LikedSongs
(
	Id SERIAL PRIMARY KEY,
	Song_Id INTEGER REFERENCES Songs(Id) ON DELETE CASCADE NOT NULL ,
	User_Id INTEGER REFERENCES Users(Id) ON DELETE CASCADE NOT NULL,
	Is_Liked Boolean,
	Date TIMESTAMP NOT NULL
);

CREATE TABLE LikedPlaylists
(
	Id SERIAL PRIMARY KEY,
	Playlist_Id INTEGER REFERENCES Playlists(Id) ON DELETE CASCADE NOT NULL,
	User_Id INTEGER REFERENCES Users(Id) ON DELETE CASCADE NOT NULL,
	Is_Liked Boolean,
	Date TIMESTAMP NOT NULL 
);

CREATE TABLE LikedCategories
(
	Id SERIAL PRIMARY KEY,
	Category_Id INTEGER REFERENCES Categories(Id) ON DELETE CASCADE NOT NULL,
	User_Id INTEGER REFERENCES Users(Id) ON DELETE CASCADE NOT NULL,
	Is_Liked Boolean,
	Date TIMESTAMP NOT NULL
);

CREATE TABLE LikedAlbums
(
	Id SERIAL PRIMARY KEY,
	Album_Id INTEGER REFERENCES Albums(Id) ON DELETE CASCADE NOT NULL,
	User_Id INTEGER REFERENCES Users(Id) ON DELETE CASCADE NOT NULL,
	Is_Liked Boolean,
	Date TIMESTAMP NOT NULL
);

CREATE TABLE LikedPerformers
(
	Id SERIAL PRIMARY KEY,
	Performer_Id INTEGER REFERENCES Performers(Id) ON DELETE CASCADE NOT NULL,
	User_Id INTEGER REFERENCES Users(Id) ON DELETE CASCADE NOT NULL,
	Is_Liked Boolean,
	Date TIMESTAMP NOT NULL
);

CREATE TABLE Bond_SongsPlaylists
(
	Song_Id INTEGER REFERENCES Songs(Id) ON DELETE CASCADE NOT NULL,
	Playlist_Id INTEGER REFERENCES Playlists(Id) ON DELETE CASCADE NOT NULL,
	PRIMARY KEY(Song_Id, Playlist_Id)
);

CREATE TABLE Bond_CategoriesPlaylists
(
	Category_Id INTEGER REFERENCES Categories(Id) ON DELETE CASCADE NOT NULL,
	Playlist_Id INTEGER REFERENCES Playlists(Id) ON DELETE CASCADE NOT NULL,
	PRIMARY KEY(Category_Id, Playlist_Id)
);

CREATE TABLE Feats
(
	Id SERIAL PRIMARY KEY,
	Song_Id INTEGER REFERENCES Songs(Id) ON DELETE CASCADE NOT NULL,
	AdditionalPerformer_Id INTEGER REFERENCES Performers(Id) ON DELETE CASCADE NOT NULL,
	UNIQUE(Song_Id, AdditionalPerformer_Id)
);

-- for examples (here is picture direct path, that is an inefficient and temporary way to set coverarts. This only works if run the app .exe from build folder)
INSERT INTO performers(nickname, login, password) VALUES('Ado', 'perf123', '777');
INSERT INTO performers(nickname, login, password) VALUES('Queen', 'perf1', '777');
INSERT INTO performers(nickname, login, password) VALUES('Dora', 'perf12', '777');
INSERT INTO genres(name, coverart) VALUES('Поп', '.\pictures\genre.png');
INSERT INTO genres(name, coverart) VALUES('Электроника','.\pictures\genre.png');
INSERT INTO genres(name, coverart) VALUES('Рок','.\pictures\genre.png');
INSERT INTO genres(name, coverart) VALUES('Метал','.\pictures\genre.png');
INSERT INTO genres(name, coverart) VALUES('Джаз','.\pictures\genre.png');
INSERT INTO genres(name, coverart) VALUES('Блюз', '.\pictures\genre.png');
INSERT INTO genres(name, coverart) VALUES('Кантри', '.\pictures\genre.png');
INSERT INTO Genres(name, coverart) VALUES('Фолк', '.\pictures\genre.png');
INSERT INTO albums(name, performer_id, coverArt, date, isPublic) VALUES('Kyogen', '1','.\pictures\KyogenAdo.png', current_timestamp, true);
INSERT INTO albums(name, performer_id, coverArt, date, isPublic) VALUES('BohemianPhapsody', '2','.\pictures\BohemianQueen.png', current_timestamp, true);
INSERT INTO albums(name, performer_id, coverArt, date, isPublic) VALUES('NewsOfTheWorld', '2','.\pictures\Queen.png', current_timestamp, true);
INSERT INTO songs(name, performer_id, album_id, genre_id) VALUES('ReadyMade', '1', '1', '1');
INSERT INTO songs(name, performer_id, album_id, genre_id) VALUES('Odo', '1', '1', '1');
INSERT INTO songs(name, performer_id, album_id, genre_id) VALUES('Freedom', '1', '1', '1');
INSERT INTO songs(name, performer_id, album_id, genre_id) VALUES('Usseewa', '1', '1', '1');
INSERT INTO songs(name, performer_id, album_id, genre_id) VALUES('Somebody To Love', '2', '2', '3');
INSERT INTO songs(name, performer_id, album_id, genre_id) VALUES('I Want To Break Free', '2', '2', '3');
INSERT INTO songs(name, performer_id, album_id, genre_id) VALUES('We Are The Champions', '2', '2', '3');
INSERT INTO users(nickname, login, password, is_moderator) VALUES('moder1', 'bestModer','300404', true);
INSERT INTO playlists(name, user_id, coverArt, date, ispublic) VALUES('1', '1', '.\pictures\Zenitsu.png', current_timestamp, true);
INSERT INTO bond_songsplaylists(song_id, playlist_id) VALUES ('5','1');
INSERT INTO bond_songsplaylists(song_id, playlist_id) VALUES ('6','1');
INSERT INTO categories(name, coverart) VALUES ('Fresh playlists','.\pictures\Rock.png');
INSERT INTO bond_categoriesplaylists(category_id, playlist_id) VALUES ('1','1');
INSERT INTO playlists(name, user_id, coverArt, date, ispublic) VALUES('For relaxation', '1', '.\1.png', current_timestamp, true);
INSERT INTO bond_songsplaylists(song_id, playlist_id) VALUES ('1','2');
INSERT INTO bond_songsplaylists(song_id, playlist_id) VALUES ('2','2');
INSERT INTO bond_categoriesplaylists(category_id, playlist_id) VALUES ('1','2');
INSERT INTO playlists(name, user_id, coverArt, date, ispublic) VALUES('new', '1', '.\pictures\randPicture.png', current_timestamp, true);
INSERT INTO albums(name, performer_id, coverArt, date, isPublic) VALUES('MISS', '3','.\pictures\MISS.png', current_timestamp, true);
INSERT INTO songs(name, performer_id, album_id, genre_id, audio) VALUES('Розовые волосы', '3', '4', '3');
INSERT INTO songs(name, performer_id, album_id, genre_id, audio) VALUES('Я боюсь людей', '3', '4', '3');
INSERT INTO bond_songsplaylists(song_id, playlist_id) VALUES ('8','3');
INSERT INTO bond_songsplaylists(song_id, playlist_id) VALUES ('9','3');
INSERT INTO bond_categoriesplaylists(category_id, playlist_id) VALUES ('1','3');
INSERT INTO categories(name, coverart) VALUES ('Золотая осень','.\pictures\osen.png');