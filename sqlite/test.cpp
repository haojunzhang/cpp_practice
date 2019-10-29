#include <iostream>
#include <string>
#include <sqlite3.h>
using namespace std;

int create_book_table(sqlite3 *db)
{
    char *error_message;
    string sql = "CREATE TABLE IF NOT EXISTS book("
                 "_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "_title TEXT NOT NULL"
                 ");";
    int response = sqlite3_exec(db, sql.c_str(), 0, 0, &error_message);
    if (response != SQLITE_OK)
    {
        cout << "create_book_table:" << error_message << endl;
        return 0;
    }
    cout << "create_book_table:success" << endl;
    return 1;
}
int insert_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("");
    return 0;
}
int insert_book(sqlite3 *db)
{
    char *error_message;
    string sql = "INSERT INTO book(_title) values ('book1');";
    int response = sqlite3_exec(db, sql.c_str(), insert_callback, 0, &error_message);
    if (response != SQLITE_OK)
    {
        cout << "insert_book:" << error_message << endl;
        return 0;
    }
    int id = sqlite3_last_insert_rowid(db);
    cout << "insert_book:success" << endl;
    cout << "insert_book:book id:" << id << endl;
    return id;
}
int select_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    cout << "\nselect_callback[START]" << endl;
    int i;
    for (i = 0; i < argc; i++)
    {
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << "select_callback[END]" << endl;
    return 0;
}
void select_book(sqlite3 *db)
{
    char *error_message;
    string sql = "SELECT * from book;";
    int response = sqlite3_exec(db, sql.c_str(), select_callback, 0, &error_message);
    if (response != SQLITE_OK)
    {
        cout << "select_book:" << error_message << endl;
        return;
    }
    cout << "select_book:success" << endl;
}
int main()
{
    string file_name = "test.db";
    sqlite3 *db;

    if (sqlite3_open(file_name.c_str(), &db))
    {
        sqlite3_close(db);
        return 0;
    }

    create_book_table(db);

    insert_book(db);

    select_book(db);

    sqlite3_close(db);
    return 0;
} // clang++ test.cpp -lsqlite3