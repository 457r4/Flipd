#include "core/Subject.hpp"
#include <string>

using namespace std;

int Subject::getId() const { return this->id_; }
string Subject::getName() const { return this->name_; }
string Subject::getSemester() const { return this->semester_; }
string Subject::getColor() const { return this->color_; }
int Subject::getGoal() const { return this->goal_; }

void Subject::setId(int id) { this->id_ = id; }
void Subject::setName(string name) { this->name_ = name; }
void Subject::setSemester(string semester) { this->semester_ = semester; }
void Subject::setColor(string color) { this->color_ = color; }
void Subject::setGoal(int goal) { this->goal_ = goal; }
