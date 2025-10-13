#ifndef SESSION_H
#define SESSION_H

#include <string>

class Session {
public:
  Session() = delete;

  static bool getActiveStatus();
  static std::string getSubject();
  static std::string getColor();
  static int getDuration();
  static void setActiveStatus(bool active);
  static void setSubject(std::string subject);
  static void setColor(std::string color);
  static void setDuration(int duration);

private:
  static bool active_;
  static std::string subject_;
  static std::string color_;
  static int duration_;
};

#endif // !SESSION_H
