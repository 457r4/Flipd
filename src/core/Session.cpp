#include "core/Session.hpp"
#include <string>

using namespace std;

bool Session::active_ = true;
std::string Session::subject_ = "";
std::string Session::color_ = "";
int Session::duration_ = 45;

bool Session::getActiveStatus() {
  return active_;
}
std::string Session::getSubject() {
  return subject_;
}
std::string Session::getColor() {
  return color_;
}
int Session::getDuration() {
  return duration_;
}

void Session::setActiveStatus(bool active) {
  Session::active_ = active;
}
void Session::setSubject(std::string subject) {
  Session::subject_ = subject;
}
void Session::setColor(std::string color) {
  Session::color_ = color;
}
void Session::setDuration(int duration) {
  Session::duration_ = duration;
}
