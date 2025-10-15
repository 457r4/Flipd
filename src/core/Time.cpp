#include "core/Time.hpp"
#include "core/Session.hpp"
#include "data/Database.hpp"
#include "ui/TUI.hpp"
#include "utils/globals.hpp"
#include <clocale>
#include <string>
#include <unistd.h>
#include <utf8cpp/utf8.h>
#include <vector>

using namespace std;

TUI* Time::tui_ = nullptr;
Session* Time::session_ = nullptr;

const string Time::zero_[5] = {"██████", "██  ██", "██  ██", "██  ██",
                               "██████"};
const string Time::one_[5] = {"  ██  ", "  ██  ", "  ██  ", "  ██  ", "  ██  "};
const string Time::two_[5] = {"██████", "    ██", "██████", "██    ", "██████"};
const string Time::three_[5] = {"██████", "    ██", "██████", "    ██",
                                "██████"};
const string Time::four_[5] = {"██  ██", "██  ██", "██████", "    ██",
                               "    ██"};
const string Time::five_[5] = {"██████", "██    ", "██████", "    ██",
                               "██████"};
const string Time::six_[5] = {"██████", "██    ", "██████", "██  ██", "██████"};
const string Time::seven_[5] = {"██████", "    ██", "    ██", "    ██",
                                "    ██"};
const string Time::eight_[5] = {"██████", "██  ██", "██████", "██  ██",
                                "██████"};
const string Time::nine_[5] = {"██████", "██  ██", "██████", "    ██",
                               "    ██"};
const string Time::dots_[5] = {"    ", " ██ ", "    ", " ██ ", "    "};

const string *Time::digits_[11] = {Time::zero_,  Time::one_,   Time::two_,
                                   Time::three_, Time::four_,  Time::five_,
                                   Time::six_,   Time::seven_, Time::eight_,
                                   Time::nine_,  Time::dots_};

string Time::time_[5];

vector<int> *Time::decomposeTime(int s) {
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
  // if (d->front() == 0)
  //   d->erase(d->begin());
  return d;
}

void Time::updateDrawing(int s) {
  vector<int> components = *decomposeTime(s);
  string content;
  for (int ln = 0; ln < 5; ln++) {
    content = "";
    for (int i = 0; i < components.size(); i++) {
      content += digits_[components[i]][ln];
      if (i != components.size() - 1)
        content += " ";
    }
    int padSize =
        (tui_->getWidth() - utf8::distance(content.begin(), content.end())) / 2;
    string padding(padSize, ' ');
    time_[ln] = padding + content;
  }
}

void Time::run(TUI *tui, Session *session) {
  tui_ = tui;
  session_ = session;
  int s = 0;
  for (s = session->getGoalDuration() * 60; s >= 0 && session_active; s--) {
    updateDrawing(s);
    tui_->refreshTimeDrawing();
    sleep(1);
  }
  session->setDuration(s);
  Database::addSession(*session);
}
