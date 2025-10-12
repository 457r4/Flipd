#ifndef TIME_H
#define TIME_H

#include <string>

using namespace std;

class Time {
public:
  string *time = new string[5];

  Time(int m);
  void update(int s);
  void run();
  ~Time();

private:
  int m;
};

#endif // !CLOCK_H
