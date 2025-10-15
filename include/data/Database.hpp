#ifndef DATABASE_H
#define DATABASE_H

#include "core/Session.hpp"
#include "core/Subject.hpp"
#include <filesystem>
#include <sqlite3.h>
#include <string>

class Database {
public:
  Database() = delete;

  static void open();
  static void close();
  static std::string get(char *param);

  static void addSemester(std::string semester_name);
  static int getSemesterIdByName(std::string semester_name);
  static void addSubject(Subject subject);
  static Subject getSubjectByName(std::string subject_name);
  static void addSession(Session session);

private:
  static const std::filesystem::path DB_DIR;
  static const std::filesystem::path DB;
  static sqlite3 *db;

  static void checkDatabaseExistence();
  static void verify(std::string related, char *errMsg);
};

#endif // !DATABASE_H
