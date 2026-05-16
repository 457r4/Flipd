#include "core/Progress.hpp"
#include "core/Subject.hpp"
#include "data/Database.hpp"
#include <cmath>
#include <cstdio>
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

std::time_t week_duration = 604800;

long long since(int when) {
  when = abs(when);
  std::time_t now = std::time(nullptr);
  std::tm local_tm = *std::localtime(&now);
  local_tm.tm_hour = 0;
  local_tm.tm_min = 0;
  local_tm.tm_sec = 0;
  local_tm.tm_mday -= local_tm.tm_wday;
  std::time_t week_start = std::mktime(&local_tm);
  return week_start - (long long)when * week_duration;
}

void progress(int when) {
  int semester_id = Database::getLastSemesterId();
  vector<Subject> subjects = Database::getSubjectsBySemesterId(semester_id);
  std::time_t since_when = since(when);

  for (Subject subject : subjects) {
    vector<Session> sessions =
        Database::getSessionsBySubject(subject, since_when);

    int total_time = 0;
    for (Session session : sessions) {
      if (session.getDate() >= since_when + week_duration)
        continue;
      if (session.getDuration() == -1) {
        total_time += session.getGoalDuration() * 60;
      } else {
        total_time += (session.getGoalDuration() * 60 - session.getDuration());
      }
    }

    printf(" %s [%d]\n", subject.getName().c_str(), subject.getGoal());
    printf("\033[3%dm", subject.getColor());
    bar(subject.getGoal() * 3600, total_time);
    printf("\033[0m\n");
  }
}
