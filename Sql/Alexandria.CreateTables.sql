CREATE TABLE IF NOT EXISTS "Continent" (
        "id"                INTEGER NOT NULL UNIQUE,
        "Name"              TEXT NOT NULL,
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "Genre" (
        "id"                INTEGER NOT NULL UNIQUE,
        "Name"              TEXT NOT NULL,
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "Language" (
        "id"                INTEGER NOT NULL UNIQUE,
        "Name"              TEXT NOT NULL,
        "AddedDate"         REAL NOT NULL,
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "Picture" (
        "id"                INTEGER NOT NULL UNIQUE,
        "Filename"          TEXT NULL,
        "Data"              BLOB NOT NULL,
        "AddedDate"         REAL NOT NULL,
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "Publisher" (
        "id"                INTEGER NOT NULL UNIQUE,
        "Name"              TEXT NOT NULL,
        "Web"               TEXT,
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "Shop" (
        "id"                INTEGER NOT NULL UNIQUE,
        "Name"              TEXT NOT NULL,
        "Web"               TEXT,
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "Email" (
        "id"                INTEGER NOT NULL UNIQUE,
        "Address"           TEXT NOT NULL,
        [AddedDate]         REAL NOT NULL,
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "Tel" (
        "id"                INTEGER NOT NULL UNIQUE,
        "Number"            TEXT NOT NULL,
        "AddedDate"         REAL NOT NULL,
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "PublisherEmails" (
        "id"                INTEGER NOT NULL UNIQUE,
        "PublisherId"       INTEGER NOT NULL,
        "EmailId"           INTEGER NOT NULL,
        FOREIGN KEY(PublisherId) REFERENCES Publisher(id),
        FOREIGN KEY(EmailId) REFERENCES Email(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "Country" (
        "id"                INTEGER NOT NULL UNIQUE,
        "Name"              TEXT NOT NULL,
        "ContinentId"       INTEGER NOT NULL,
        FOREIGN KEY(ContinentId) REFERENCES Continent(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "Address" (
        "id"                INTEGER NOT NULL UNIQUE,
        "City"              TEXT NOT NULL,
        "State"             TEXT,
        "CountryId"         INTEGER NOT NULL,
        "Description"       TEXT NOT NULL,
        "AddedDate"         REAL NOT NULL,
        FOREIGN KEY(CountryId) REFERENCES Counrtry(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "ShopAddresses" (
        "id"                INTEGER NOT NULL UNIQUE,
        [ShopId]            INTEGER NOT NULL,
        [AddressId]         INTEGER NOT NULL,
        FOREIGN KEY(ShopId) REFERENCES Shop(id),
        FOREIGN KEY(AddressId) REFERENCES Address(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "ShopEmails" (
        "id"                INTEGER NOT NULL UNIQUE,
        "ShopId"            INTEGER NOT NULL,
        "EmailId"           INTEGER NOT NULL,
        FOREIGN KEY(ShopId) REFERENCES Shop(id),
        FOREIGN KEY(EmailId) REFERENCES Email(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "ShopTels" (
        "id"                INTEGER NOT NULL UNIQUE,
        "ShopId"            INTEGER NOT NULL,
        "TelId"             INTEGER NOT NULL,
        FOREIGN KEY(ShopId) REFERENCES Shop(id),
        FOREIGN KEY(TelId) REFERENCES Tel(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "PublisherAddresses" (
        "id"                INTEGER NOT NULL UNIQUE,
        "PublisherId"       INTEGER NOT NULL,
        "AddressId"         INTEGER NOT NULL,
        FOREIGN KEY(PublisherId) REFERENCES Publisher(id),
        FOREIGN KEY(AddressId) REFERENCES Address(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "PublisherTels" (
        "id"                INTEGER NOT NULL UNIQUE,
        "PublisherId"       INTEGER NOT NULL,
        "TelId"             INTEGER NOT NULL,
        FOREIGN KEY(PublisherId) REFERENCES Publisher(id),
        FOREIGN KEY(TelId) REFERENCES Tel(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "Book" (
        "id"                INTEGER NOT NULL UNIQUE,
        "Name"              TEXT NOT NULL,
        "Pages"             INTEGER,
        "PublisherId"       INTEGER NOT NULL,
        "LanguageId"        INTEGER NOT NULL,
        "ShopId"            INTEGER
        "IsRead"            INTEGER NOT NULL,
        "LastReadDate"      REAL,
        "ReleaseDate"       REAL,
        "Price"             INTEGER,
        "PurchasedDay"      REAL,
        "AddDate"           REAL,
        "ModifiedDate"      REAL,
        FOREIGN KEY(PublisherId) REFERENCES Publisher(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "Author" (
        "id"                INTEGER NOT NULL UNIQUE,
        "FirstName"         TEXT NOT NULL,
        "MiddleName"        TEXT,
        "LastName"          TEXT NOT NULL,
        "Fullname"          TEXT NOT NULL,
        "CountryId"         INTEGER NOT NULL,
        "DateOfBirth"       REAL NOT NULL,
        "AddedDate"         REAL NOT NULL,
        "ModifiedDate"      REAL,
        "Note"              TEXT,
        FOREIGN KEY(CountryId) REFERENCES Country(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "AuthorPictures" (
        "id"                INTEGER NOT NULL UNIQUE,
        "AuthorId"          INTEGER NOT NULL,
        "PictureId"         INTEGER NOT NULL,
        FOREIGN KEY(AuthorId) REFERENCES Author(id),
        FOREIGN KEY(PictureId) REFERENCES Picture(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);

CREATE TABLE IF NOT EXISTS "BookAuthors" (
        "id"                INTEGER NOT NULL UNIQUE,
        "BookId"            INTEGER NOT NULL,
        "AuthorId"          INTEGER NOT NULL,
        FOREIGN KEY(BookId) REFERENCES Book(id),
        FOREIGN KEY(AuthorId) REFERENCES Author(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);


CREATE TABLE IF NOT EXISTS "BookGenres" (
        "id"                INTEGER NOT NULL UNIQUE,
        "GenreId"           INTEGER NOT NULL,
        "BookId"            INTEGER NOT NULL,
        FOREIGN KEY(GenreId) REFERENCES Genre(id),
        FOREIGN KEY(BookId) REFERENCES Book(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);


CREATE TABLE IF NOT EXISTS "BookPictures" (
        "id"                INTEGER NOT NULL UNIQUE,
        "BookId"            INTEGER NOT NULL,
        "PictureId"         INTEGER NOT NULL,
        FOREIGN KEY(BookId) REFERENCES Book(id),
        FOREIGN KEY(PictureId) REFERENCES Picture(id),
        PRIMARY KEY("id" AUTOINCREMENT)
);
