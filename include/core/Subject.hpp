#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>

class Subject {
public:
  Subject() = default;
  ~Subject() = default;

  int getId() const;
  std::string getName() const;
  std::string getSemester() const;
  int getColor() const;
  int getGoal() const;

  void setId(int id_);
  void setName(std::string name);
  void setSemester(std::string semester);
  void setColor(int color);
  void setGoal(int goal);

private:
  int id_ = -1;
  std::string name_ = "";
  std::string semester_ = "";
  int color_ = 7;
  int goal_ = 0;
};

#endif // !SUBJECT_H
