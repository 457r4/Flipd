#include "core/ActivityMonitor.hpp"
#include "data/Database.hpp"
#include "core/Session.hpp"
#include "libs/cxxopts.hpp"
#include "ui/TUI.hpp"
#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char *argv[]) {

  cxxopts::Options options("Flipd", "Improve your study habits");
  options.add_options()("h,help", "Print this message")(
      "add", "Create a new subject, must belong to a semester. Cannot start a session with add", cxxopts::value<string>())(
      "subject", "Latest semester subject will be used, use this option to change or set the subject's color, weekly goal or the duration of a session about to start", cxxopts::value<string>())(
      "semester", "Create a new semester (will group subjects)",
      cxxopts::value<string>())(
      "color", "Give a color to the subject (white, green, red, blue, yellow, magenta, cyan, black)", cxxopts::value<int>())(
      "goal", "Set a weekly goal in hours for this subject", cxxopts::value<int>())(
      "duration", "Study session duration in minutes", cxxopts::value<int>());
  options.parse_positional({"subject", "duration"});

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    cout << options.help() << endl;
    return 0;
  }

  Session session;
  Subject subject;

  Database::open();

  if (!result.count("add") && result.count("semester")) {
    Database::addSemester(result["semester"].as<string>());
    return 0;
  }

  // Improve system of verification of semester, color and goal

  if (result.count("add")) {
    if (!result.count("semester")) {
      cerr << "You must provide a semester" << endl;
      return 1;
    }
    subject.setName(result["add"].as<string>());
    subject.setSemester(result["semester"].as<string>());
    if (result.count("color")) subject.setColor(result["color"].as<int>());
    if (result.count("goal")) subject.setGoal(result["goal"].as<int>());
    Database::addSubject(subject);
    return 0;
  }

  if (!result.count("subject")) {
    cerr << "Cannot start a session" << endl;
    return 1;
  } else {
    // Verify subject existence
    subject.setName(result["subject"].as<string>());
  }
  if (!result.count("duration")) {
    if (result.count("semester")) {
      // Verify semester's existence
      subject.setSemester(result["semester"].as<string>());
    }
    if (result.count("color")) {
      // Verify if color is valid
      subject.setColor(result["color"].as<int>());
    }
    if (result.count("goal")) {
      // Verify if goal is valid
      subject.setGoal(result["goal"].as<int>());
    }
    session.setSubject(subject);
    return 0;
  } else {
    // Verify duration
    subject = Database::getSubjectByName(result["subject"].as<string>());
    session.setSubject(subject);
    session.setGoalDuration(result["duration"].as<int>());
  }

  thread th(ActivityMonitor::monitor);
  th.detach();
  TUI tui(session);
  tui.start();

  return 0;
}
