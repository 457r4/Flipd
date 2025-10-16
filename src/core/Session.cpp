#include "core/Session.hpp"
#include "core/Subject.hpp"

bool Session::getActiveStatus() const { return this->active_; }
Subject Session::getSubject() const { return this->subject_; }
long long Session::getDate() const { return this->date_; }
int Session::getGoalDuration() const { return this->goal_duration_; }
int Session::getDuration() const { return this->duration_; }

void Session::setActiveStatus(bool active) { this->active_ = active; }
void Session::setSubject(Subject subject) { this->subject_ = subject; }
void Session::setDate(long long date) { this->date_ = date; }
void Session::setGoalDuration(int goal_duration) {
  this->goal_duration_ = goal_duration;
}
void Session::setDuration(int duration) { this->duration_ = duration; }
