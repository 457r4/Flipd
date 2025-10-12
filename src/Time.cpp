#include "Time.hpp"
#include "TUI.hpp"
#include "globals.hpp"
#include <clocale>
#include <string>
#include <iostream>
#include <unistd.h>
#include <utf8cpp/utf8.h>
#include <vector>

using namespace std;

const string zero[5] = {"███████", "██   ██", "██   ██", "██   ██", "███████"};
const string one[5] = {"██", "██", "██", "██", "██"};
const string two[5] = {"██████", "    ██", "██████", "██    ", "██████"};
const string three[5] = {"██████", "    ██", "██████", "    ██", "██████"};
const string four[5] = {"██  ██", "██  ██", "██████", "    ██", "    ██"};
const string five[5] = {"██████", "██    ", "██████", "    ██", "██████"};
const string six[5] = {"██████", "██    ", "██████", "██  ██", "██████"};
const string seven[5] = {"██████", "    ██", "    ██", "    ██", "    ██"};
const string eight[5] = {"██████", "██  ██", "██████", "██  ██", "██████"};
const string nine[5] = {"██████", "██  ██", "██████", "    ██", "    ██"};
const string dots[5] = {"  ", "██", "  ", "██", "  "};

const string *digits[11] = {zero, one,   two,   three, four, five,
                            six,  seven, eight, nine,  dots};

vector<int> *decomposeTime(int s) {
  vector<int> *d = new vector<int>;
  int components[3] = {0, 0, 0};
  components[2] = s % 60;
  s -= components[2];
  components[1] = (s / 60) % 60;
  s = s / 60 - components[1];
  components[0] = s / 60;
  for (int i = 0; i < 3; i++) {
    if (i == 0 && components[i] == 0)
      continue;
    d->push_back((components[i] - components[i] % 10) / 10);
    d->push_back(components[i] % 10);
    if (i != 2)
      d->push_back(10);
  }
  if (d->front() == 0)
    d->erase(d->begin());
  return d;
}

void Time::update(int s) {
  delete[] time;
  time = new string[5];
  vector<int> componenta = *decomposeTime(s);
  string content;
  for (int ln = 0; ln < 5; ln++) {
    content = "";
    for (int i = 0; i < componenta.size(); i++) {
      content += digits[componenta[i]][ln];
      if (i != componenta.size() - 1)
        content += " ";
    }
    int padSize =
        (TUI::getWidth() - utf8::distance(content.begin(), content.end())) / 2;
    string padding(padSize, ' ');
    time[ln] = padding + content;
  }
}

void Time::run() {
  for (int s = m * 60; s >= 0 && session_active; s--) {
    update(s);
    TUI::refreshTime();
    sleep(1);
  }
}

Time::Time(int m) {
  this->m = m;
  update(m * 60);
}
