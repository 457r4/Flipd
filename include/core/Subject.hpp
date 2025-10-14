#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>

class Subject {
public:
  Subject() = default;
  ~Subject() = default;

  std::string getName() const;
  std::string getSemester() const;
  std::string getColor() const;
  int getGoal() const;

  void setName(std::string name);
  void setSemester(std::string semester);
  void setColor(std::string color);
  void setGoal(int goal);

private:
  std::string name_ = "";
  std::string semester_ = "";
  std::string color_ = "white";
  int goal_ = 0;
};

#endif // !SUBJECT_H
