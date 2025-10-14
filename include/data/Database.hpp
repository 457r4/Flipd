#ifndef DATABASE_H
#define DATABASE_H

#include <filesystem>
#include <sqlite3.h>
#include <string>

class Database {
public:
  Database() = delete;

  static void open();
  static void close();
  static std::string get(char *param);
  static void newTable(char *subject);

private:
  static const std::filesystem::path DB_DIR;
  static const std::filesystem::path DB;
  static sqlite3 *db;

  static void checkDatabaseExistence();
};

#endif // !DATABASE_H
