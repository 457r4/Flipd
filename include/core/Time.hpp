#ifndef TIME_H
#define TIME_H

#include <string>

using namespace std;

class Time {
public:
  Time() = delete;

  static std::string time_[5];

  static void run(int m);

private:
  static const std::string zero_[5];
  static const std::string one_[5];
  static const std::string two_[5];
  static const std::string three_[5];
  static const std::string four_[5];
  static const std::string five_[5];
  static const std::string six_[5];
  static const std::string seven_[5];
  static const std::string eight_[5];
  static const std::string nine_[5];
  static const std::string dots_[5];
  static const std::string *digits_[11];

  static vector<int> *decomposeTime(int s);
  static void updateDrawing(int s);
};

#endif // !TIME_H
