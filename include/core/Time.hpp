#ifndef TIME_H
#define TIME_H

#include <string>

using namespace std;

class Time {
public:
  Time() = delete;

  static string time_[5];

  static void run(int m);

private:
  static const string zero_[5];
  static const string one_[5];
  static const string two_[5];
  static const string three_[5];
  static const string four_[5];
  static const string five_[5];
  static const string six_[5];
  static const string seven_[5];
  static const string eight_[5];
  static const string nine_[5];
  static const string dots_[5];
  static const string *digits_[11];

  static vector<int> *decomposeTime(int s);
  static void updateDrawing(int s);
};

#endif // !TIME_H
