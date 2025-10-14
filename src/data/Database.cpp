#include "data/Database.hpp"
#include "core/Session.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

const filesystem::path Database::DB_DIR =
    "/data/data/com.termux/files/home/.local/share/flipd";
const filesystem::path Database::DB = DB_DIR / "study.db";

sqlite3 *Database::db = nullptr;
int r;

void verify(string related, char *errMsg) {
  if (r != SQLITE_OK) {
    cerr << related << ":: " << errMsg << endl;
    sqlite3_free(errMsg);
  }
}

void Database::open() {
  r = sqlite3_open(DB.c_str(), &db);
  verify("Error opening database", (char *)sqlite3_errmsg(db));
  const char *sql_semesters = "CREATE TABLE IF NOT EXISTS Semesters ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "name TEXT NOT NULL);";
  const char *sql_subjects = "CREATE TABLE IF NOT EXISTS Subjects ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "name TEXT NOT NULL,"
                             "semester_id INTEGER NOT NULL,"
                             "color TEXT,"
                             "goal INTEGER NOT NULL,"
                             "FOREIGN KEY(semester_id) REFERENCES Semesters(id));";
  const char *sql_sessions = "CREATE TABLE IF NOT EXISTS Sessions ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "subject_id INTEGER NOT NULL,"
                             "date INTEGER NOT NULL,"
                             "goal_duration INTEGER NOT NULL,"
                             "duration INTEGER NOT NULL,"
                             "FOREIGN KEY(subject_id) REFERENCES Subjects(id));";
  char *errMsg = nullptr;
  r = sqlite3_exec(db, sql_semesters, nullptr, nullptr, &errMsg);
  verify("Error creating table", errMsg);
  r = sqlite3_exec(db, sql_subjects, nullptr, nullptr, &errMsg);
  verify("Error creating table", errMsg);
  r = sqlite3_exec(db, sql_sessions, nullptr, nullptr, &errMsg);
}

void Database::close() { sqlite3_close(db); }

// string Database::get(char *param) {}

void Database::checkDatabaseExistence() {
  if (!filesystem::exists(DB_DIR)) {
    filesystem::create_directory(DB_DIR);
  }
  if (!filesystem::exists(DB)) {
    ofstream ofs(DB);
  }
}
