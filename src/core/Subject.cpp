#include "core/Subject.hpp"
#include <string>

int Subject::getId() const { return this->id_; }
std::string Subject::getName() const { return this->name_; }
std::string Subject::getSemester() const { return this->semester_; }
int Subject::getColor() const { return this->color_; }
int Subject::getGoal() const { return this->goal_; }

void Subject::setId(int id) { this->id_ = id; }
void Subject::setName(std::string name) { this->name_ = name; }
void Subject::setSemester(std::string semester) { this->semester_ = semester; }
void Subject::setColor(int color) { this->color_ = color; }
void Subject::setGoal(int goal) { this->goal_ = goal; }
