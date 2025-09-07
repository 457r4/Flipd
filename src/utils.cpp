#include "utils.h"
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>

std::filesystem::path LOG_DIR =
    "/data/data/com.termux/files/home/.local/share/flipd";
std::filesystem::path LOG_REG = LOG_DIR / "flipd.log";

std::string date() {
  time_t timestamp = time(NULL);
  struct tm datetime = *localtime(&timestamp);
  char output[50];
  strftime(output, 50, "%y/%m/%d %H:%M:%S", &datetime);
  return output;
}

void checkLogExistence() {
  if (!std::filesystem::exists(LOG_DIR)) {
    std::filesystem::create_directories(LOG_DIR);
  }
  if (!std::filesystem::exists(LOG_REG)) {
    std::ofstream ofs(LOG_REG);
  }
}

void log(std::string message) {
  checkLogExistence();
  std::ofstream log(LOG_REG, std::ios::app);
  log << date() << " :: " << message << std::endl;
}
