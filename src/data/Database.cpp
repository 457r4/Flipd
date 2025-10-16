#include "data/Database.hpp"
#include "core/Session.hpp"
#include "core/Subject.hpp"
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

void Database::verify(string related, char *errMsg = nullptr) {
  if (r != SQLITE_OK && r != SQLITE_DONE && r != SQLITE_ROW) {
    cerr << related << ":: " << sqlite3_errmsg(db) << endl;
    if (errMsg)
      sqlite3_free(errMsg);
  }
}

void Database::open() {
  r = sqlite3_open(DB.c_str(), &db);
  verify("Error opening database", (char *)sqlite3_errmsg(db));
  const char *sql_semesters = "CREATE TABLE IF NOT EXISTS Semesters ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "name TEXT NOT NULL);";
  const char *sql_subjects =
      "CREATE TABLE IF NOT EXISTS Subjects ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "name TEXT NOT NULL,"
      "semester_id INTEGER NOT NULL,"
      "color INTEGER,"
      "goal INTEGER NOT NULL,"
      "FOREIGN KEY(semester_id) REFERENCES Semesters(id));";
  const char *sql_sessions =
      "CREATE TABLE IF NOT EXISTS Sessions ("
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

void Database::addSemester(string semester_name) {
  const char *sql = "INSERT INTO Semesters (name) VALUES (?);";
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  sqlite3_bind_text(stmt, 1, semester_name.c_str(), -1, SQLITE_TRANSIENT);
  r = sqlite3_step(stmt);
  verify("Error inserting semester", (char *)sqlite3_errmsg(db));
  sqlite3_finalize(stmt);
}

int Database::getSemesterIdByName(string semester_name) {
  const char *sql = "SELECT id FROM Semesters WHERE name = ?;";
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  sqlite3_bind_text(stmt, 1, semester_name.c_str(), -1, SQLITE_TRANSIENT);
  int semester_id = -1;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    semester_id = sqlite3_column_int(stmt, 0);
  }
  sqlite3_finalize(stmt);
  return semester_id;
}

void Database::addSubject(Subject subject) {
  const char *sql = "INSERT INTO Subjects (name, semester_id, color, goal) "
                    "VALUES (?, ?, ?, ?);";
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  sqlite3_bind_text(stmt, 1, subject.getName().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 2, getSemesterIdByName(subject.getSemester()));
  sqlite3_bind_int(stmt, 3, subject.getColor());
  sqlite3_bind_int(stmt, 4, subject.getGoal());

  r = sqlite3_step(stmt);
  verify("Error inserting subject", (char *)sqlite3_errmsg(db));
  sqlite3_finalize(stmt);
}

Subject Database::getSubjectByName(string subject_name) {
  const char *sql = "SELECT id, name, color, goal FROM Subjects WHERE name = ?;";
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  sqlite3_bind_text(stmt, 1, subject_name.c_str(), -1, SQLITE_TRANSIENT);
  Subject subject;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    subject.setId(sqlite3_column_int(stmt, 0));
    subject.setName(subject_name);
    subject.setColor(sqlite3_column_int(stmt, 2));
    subject.setGoal(sqlite3_column_int(stmt, 3));
  }
  sqlite3_finalize(stmt);
  return subject;
}

void Database::addSession(Session session) {
  const char *sql = "INSERT INTO Sessions (subject_id, date, goal_duration, "
                    "duration) VALUES (?, ?, ?, ?);";
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  sqlite3_bind_int64(stmt, 1,
                   getSubjectByName(session.getSubject().getName()).getId());
  sqlite3_bind_int(stmt, 2, session.getDate());
  sqlite3_bind_int(stmt, 3, session.getGoalDuration());
  sqlite3_bind_int(stmt, 4, session.getDuration());

  r = sqlite3_step(stmt);
  verify("Error inserting session", (char *)sqlite3_errmsg(db));
  sqlite3_finalize(stmt);
}

void Database::checkDatabaseExistence() {
  if (!filesystem::exists(DB_DIR)) {
    filesystem::create_directory(DB_DIR);
  }
  if (!filesystem::exists(DB)) {
    ofstream ofs(DB);
  }
}
