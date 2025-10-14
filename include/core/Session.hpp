#ifndef SESSION_H
#define SESSION_H

#include "core/Subject.hpp"

class Session {
public:
  Session() = default;
  ~Session() = default;

  bool getActiveStatus() const;
  Subject getSubject() const;
  int getDate() const;
  int getGoalDuration() const;
  int getDuration() const;

  void setActiveStatus(bool active);
  void setSubject(Subject subject);
  void setDate(int date);
  void setGoalDuration(int goal_duration);
  void setDuration(int duration);

private:
  bool active_ = true;
  Subject subject_;
  int date_ = 0;
  int goal_duration_ = 45;
  int duration_ = 0;
};

#endif // !SESSION_H
