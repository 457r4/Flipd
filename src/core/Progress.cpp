#include "core/Progress.hpp"
#include "core/Subject.hpp"
#include "data/Database.hpp"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

using namespace std;

void bar(int goal, int prog) {
  float percentage = (float)prog / goal;
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int width = (w.ws_col >= 80) ? 80 : w.ws_col;
  int max_len = width - 7;
  cout << " ";
  if (percentage >= 1) {
    for (int i = 0; i < max_len; i++)
      cout << "█";
  } else {
    int length = (int)(max_len * percentage);
    for (int i = 0; i < length; i++)
      cout << "█";
    for (int i = 0; i < max_len - length; i++)
      cout << "░";
  }
  printf("%*d%%\n", 4, (int)(percentage * 100));
}

long long since() {
  std::time_t now = std::time(nullptr);
  std::tm local_tm = *std::localtime(&now);
  local_tm.tm_hour = 0;
  local_tm.tm_min = 0;
  local_tm.tm_sec = 0;
  local_tm.tm_mday -= local_tm.tm_wday;
  std::time_t week_start = std::mktime(&local_tm); // 7
  return week_start;
}

void progress() {
  int semester_id = Database::getLastSemesterId();
  vector<Subject> subjects = Database::getSubjectsBySemesterId(semester_id);
  for (Subject subject : subjects) {
    printf(" %s [%d]\n", subject.getName().c_str(), subject.getGoal());
    vector<Session> sessions = Database::getSessionsBySubject(subject, since());
    int total_time = 0;
    for (Session session : sessions) {
      if (session.getDuration() == -1) {
        total_time += session.getGoalDuration() * 60;
      } else {
        total_time += (session.getGoalDuration() * 60 - session.getDuration());
      }
    }
    printf("\033[3%dm", subject.getColor());
    bar(subject.getGoal() * 3600, total_time);
    printf("\033[0m\n");
  }
}
