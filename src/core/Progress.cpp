#include "core/Progress.hpp"
#include "core/Subject.hpp"
#include "data/Database.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
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

void total(int when) {
  int semester_id = Database::getLastSemesterId();
  vector<Subject> subjects = Database::getSubjectsBySemesterId(semester_id);
  std::time_t since_when = since(when);

  int total_time = 0;
  for (Subject subject : subjects) {
    vector<Session> sessions =
        Database::getSessionsBySubject(subject, since_when);
    for (Session session : sessions) {
      if (session.getDate() >= since_when + week_duration)
        continue;
      if (session.getDuration() == -1) {
        total_time += session.getGoalDuration() * 60;
      } else {
        total_time += (session.getGoalDuration() * 60 - session.getDuration());
      }
    }
  }

  int hours = total_time / 3600;
  int minutes = (total_time % 3600) / 60;
  int seconds = total_time % 60;

  (when == 0)
      ? printf("You've studied \033[97m%02d:%02d:%02d\033[0m this week\n",
               hours, minutes, seconds)
      : printf("You've studied \033[97m%02d:%02d:%02d\033[0m %d weeks ago\n",
               hours, minutes, seconds, abs(when));
}

void streak() {
  std::time_t day_duration = 86400;
  std::time_t now = std::time(nullptr);
  std::tm local_tm = *std::localtime(&now);
  local_tm.tm_hour = 0;
  local_tm.tm_min = 0;
  local_tm.tm_sec = 0;
  std::time_t day_start = std::mktime(&local_tm);

  int semester_id = Database::getLastSemesterId();
  vector<Subject> subjects = Database::getSubjectsBySemesterId(semester_id);

  int streak = 0;
  int time_today = 0;

  vector<long long> session_dates;

  for (Subject subject : subjects) {
    vector<Session> sessions = Database::getSessionsBySubject(subject, 0);
    for (Session session : sessions) {
      if (session.getDate() >= day_start) {
        if (session.getDuration() == -1) {
          time_today += session.getGoalDuration() * 60;
        } else {
          time_today +=
              (session.getGoalDuration() * 60 - session.getDuration());
        }
      }
      session_dates.push_back(session.getDate());
    }
  }

  int i = 0;
  bool break_streak = false;
  while (!break_streak) {
    std::time_t streak_start = day_start - i * day_duration;
    break_streak = !std::any_of(session_dates.begin(), session_dates.end(),
                                [streak_start, day_duration](long long date) {
                                  return streak_start <= date &&
                                         date < streak_start + day_duration;
                                });
    streak++;
    i++;
  }

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int width = w.ws_col;

  int hours = time_today / 3600;
  int minutes = (time_today % 3600) / 60;

  char left[256], right[256], right_raw[256];
  snprintf(left, sizeof(left), "today %02d:%02d", hours, minutes);
  snprintf(right, sizeof(right), "\033[90m\033[0m\033[100m%dd 󰈸\033[0m\033[90m\033[0m", streak);
  snprintf(right_raw, sizeof(right_raw), "%dd 󰈸", streak);

  printf(" %s─────────────────────────%s\n", "╭", "╮");
  printf(" │ %-*s%s │\n", 30 - (int)(strlen(right_raw)), left, right);
  printf(" %s─────────────────────────%s\n", "╰", "╯");
  // printf(" %-*s%s\n", 10, "╰", "╯");
}
