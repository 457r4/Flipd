#ifndef SESSION_H
#define SESSION_H

#include "core/Subject.hpp"

class Session {
public:
  Session() = default;
  ~Session() = default;

  bool getActiveStatus() const;
  Subject getSubject() const;
  long long getDate() const;
  int getGoalDuration() const;
  int getDuration() const;

  void setActiveStatus(bool active);
  void setSubject(Subject subject);
  void setDate(long long date);
  void setGoalDuration(int goal_duration);
  void setDuration(int duration);

private:
  bool active_ = true;
  Subject subject_;
  long long date_ = 0;
  int goal_duration_ = 45;
  int duration_ = 0;
};

#endif // !SESSION_H
